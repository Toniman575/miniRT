/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:05:14 by sancuta           #+#    #+#             */
/*   Updated: 2026/05/12 17:12:24 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

//TODO: consider whether alignment needs to be 8 in arena_mem* functions
//      i think it should be 8, as the natural alignment of 64bit OS
size_t	arena_memcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size, 8);
	ft_memcpy(dest->buf + offset, src, size);
	return (offset);
}

size_t	arena_memset(t_arena *data, int c, size_t size)
{
	size_t	offset;

	offset = arena_alloc(data, size, 8);
	ft_memset(data->buf + offset, c, size);
	return (offset);
}

size_t	arena_strlcpy(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size, 1);
	ft_strlcpy(dest->buf + offset, src, size);
	return (offset);
}

size_t	arena_strlcat(t_arena *dest, const void *src, size_t size)
{
	size_t	offset;

	offset = arena_alloc(dest, size - 1, 1);
	ft_strlcpy(dest->buf + offset - 1, src, size);
	return (offset);
}
