/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:09:53 by asadik            #+#    #+#             */
/*   Updated: 2026/10/28 00:06:46 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_mlx(t_state *state)
{
	state->mlx_ptr = mlx_init();
	if (!state->mlx_ptr)
		handle_exit(state, (t_exit_data){"minirt", "init_mlx",
			E_MLX_INIT,  EXIT_FAILURE});
	state->win.ptr = mlx_new_window(state->mlx_ptr,
			state->win.dim.width, state->win.dim.height, "miniRT");
	if (!state->win.ptr)
		handle_exit(state, (t_exit_data){"minirt", "init_mlx",
			E_MLX_WIN, EXIT_FAILURE});
	state->img.ptr = mlx_new_image(state->mlx_ptr,
			state->img.dim.width, state->img.dim.height);
	if (!state->img.ptr)
		handle_exit(state, (t_exit_data){"minirt", "init_mlx",
			E_MLX_IMG, EXIT_FAILURE});
	state->img.buf = mlx_get_data_addr(state->img.ptr,
			&state->img.bits_per_pixel, &state->img.bytes_per_line,
			&state->img.byte_order);
}

void	init_dim(t_state *state)
{
	state->win.dim = (t_dim2d){WIN_WIDTH, WIN_HEIGHT};
	state->img.dim = (t_dim2d){IMG_WIDTH, IMG_HEIGHT};
}

/// TODO: Should file be in state?

void	init(t_state *state, char *file)
{
	state = ft_memset(state, 0, sizeof(t_state));
	//parse(&state, file);
	init_dim(state);
	init_mlx(state);
	mlx_hook(state->win.ptr, KeyPress, KeyPressMask, handle_key_press, state);
	mlx_hook(state->win.ptr, KeyRelease, KeyReleaseMask,
			handle_key_release, state);
	mlx_loop_hook(state->mlx_ptr, render, state);
	mlx_hook(state->win.ptr, ClientMessage, StructureNotifyMask,
			call_exit, state);
}
