/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 21:21:17 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/04 20:02:18 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	cleanup(t_state *state)
{
	if (state->img.ptr)
		mlx_destroy_image (state->mlx_ptr, state->img.ptr);
	if (state->win.ptr)
		mlx_destroy_window(state->mlx_ptr, state->win.ptr);
	if (state->mlx_ptr)
	{
		mlx_loop_end(state->mlx_ptr);
		mlx_destroy_display(state->mlx_ptr);
		free(state->mlx_ptr);
	}
	arena_free(&state->objects);
	get_next_line(-255);
}

void	handle_exit(t_state *state, t_exit_data data)
{
	handle_status_msg(data);
	cleanup(state);
	exit(data.status);
}
