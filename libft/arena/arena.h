/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:41:35 by sancuta           #+#    #+#             */
/*   Updated: 2026/08/09 13:00:24 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include "../libft.h"
# define HALF_SIZE_MAX 9223372036854775807

typedef struct s_arena
{
	char	*buf;
	size_t	offset;
	size_t	cap;
	size_t	stride;
	void	(*clean)(void *);
	void	*env;
}	t_arena;

t_arena		arena_init(size_t cap, size_t stride);
size_t		arena_alloc(t_arena *arena, size_t size, size_t align);
void		arena_reset(t_arena *arena);
void		arena_clear(t_arena *arena);
size_t		arena_memset(t_arena *data, int c, size_t size);
size_t		arena_memcpy(t_arena *dest, const void *src, size_t size);
size_t		arena_strlcpy(t_arena *dest, const void *src, size_t size);
size_t		arena_strlcat(t_arena *dest, const void *src, size_t size);
size_t		arena_itoa(t_arena *dest, const int nbr);
size_t		arena_split(t_arena *dest, const char *src, char del);
size_t		arena_save(t_arena *arena);
void		arena_restore(t_arena *arena, size_t idx);
void		arena_hook_cleanup(t_arena *arena, void (*clean)(void *),
				void *env);
void		arena_free(t_arena *arena);
uint64_t	get_idx_from_offset(t_arena *arena, uint64_t offset);
uint64_t	get_offset_from_idx(t_arena *arena, uint64_t idx);
void		*get_ptr_from_offset(t_arena *arena, uint64_t offset);
void		*get_ptr_from_idx(t_arena *arena, uint64_t idx);
void		*get_ptr_from_top(t_arena *arena, uint32_t idx);
#endif
