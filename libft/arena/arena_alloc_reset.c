/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_reset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/27 08:49:27 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "arena.h"

/*
 * natural alignment of 64bit systems is 8
 */

static inline void	arena_align(t_arena *arena, size_t align)
{
	arena->offset = (arena->offset + (align - 1)) & ~(align - 1);
}

static void	arena_grow_error_handler(t_arena *arena, t_exit_data exit_data)
{
	handle_status_msg(exit_data);
	if (arena->clean && arena->env)
		arena->clean(arena->env);
	arena_free(arena);
	exit(exit_data.status);
}

static void	arena_grow(t_arena *arena, size_t size)
{
	void	*new_buffer;

	while (arena->cap + arena->stride - arena->offset < size)
	{
		if (arena->cap > HALF_SIZE_MAX)
			arena_grow_error_handler(arena, (t_exit_data){NULL, "arena_grow",
				"arena too big", EXIT_FAILURE});
		arena->cap *= 2;
	}
	errno = 0;
	new_buffer = malloc(arena->cap + arena->stride);
	if (!new_buffer && errno)
		arena_grow_error_handler(arena, (t_exit_data){NULL, "arena_grow",
			strerror(errno), EXIT_FAILURE});
	ft_memmove(new_buffer, arena->buf, arena->offset);
	ft_memset(new_buffer + arena->offset, 0,
		arena->cap + arena->stride - arena->offset);
	free(arena->buf);
	arena->buf = new_buffer;
}

size_t	arena_alloc(t_arena *arena, size_t size, size_t align)
{
	size_t	offset;

	arena_align(arena, align);
	if (size > (arena->cap + arena->stride - arena->offset))
		arena_grow(arena, size);
	offset = arena->offset;
	arena->offset += size;
	return (offset);
}
