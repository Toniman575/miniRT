/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 13:11:08 by sancuta           #+#    #+#             */
/*   Updated: 2026/08/09 13:11:23 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	arena_reset(t_arena *arena)
{
	arena->offset = arena->stride;
}

void	arena_clear(t_arena *arena)
{
	ft_memset(arena->buf + arena->stride, 0, arena->offset - arena->stride);
	arena->offset = arena->stride;
}
