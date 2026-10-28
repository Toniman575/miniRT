/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:27:38 by sancuta           #+#    #+#             */
/*   Updated: 2026/08/09 13:00:50 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

uint64_t	get_idx_from_offset(t_arena *arena, uint64_t offset)
{
	return (offset / arena->stride);
}

uint64_t	get_offset_from_idx(t_arena *arena, uint64_t idx)
{
	return (idx * arena->stride);
}

void	*get_ptr_from_offset(t_arena *arena, uint64_t offset)
{
	return (arena->buf + offset);
}

void	*get_ptr_from_idx(t_arena *arena, uint64_t idx)
{
	return (arena->buf + idx * arena->stride);
}

void	*get_ptr_from_top(t_arena *arena, uint32_t idx)
{
	uint64_t	offset;

	offset = arena->offset - idx * arena->stride;
	return (get_ptr_from_offset(arena, offset));
}
