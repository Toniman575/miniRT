/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:09:53 by asadik            #+#    #+#             */
/*   Updated: 2026/11/04 14:14:52 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"

void	init_mlx(t_state *state)
{
	state->mlx_ptr = mlx_init();
	if (!state->mlx_ptr)
		handle_exit(state, (t_exit_data){"minirt", "init_mlx",
			E_MLX_INIT, EXIT_FAILURE});
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

void	init_dummy(t_state *state)
{
	t_camera	cam = {
		.pos = {0., 0., 0.},
		.rotation = {1., 0., 0., 0.},
		.pan_speed = 0.1,
		.rot_speed = 0.05,
		.fov = 70.0
	};
	state->camera = cam;
	state->objects = malloc(sizeof(t_object) * 3);
	state->objects_n = 3;
	state->objects[0].type = OBJ_SPHERE;
	state->objects[0].data.sphere.center = new_world_coord(0., 0., -5.);
	state->objects[0].data.sphere.diameter = 2.;
	state->objects[0].color = new_color(255, 0, 0);
	state->objects[1].type = OBJ_SPHERE;
	state->objects[1].data.sphere.center = new_world_coord(2., 0., -6.);
	state->objects[1].data.sphere.diameter = 2.;
	state->objects[1].color = new_color(0, 255, 0);
	state->objects[2].type = OBJ_PLANE;
	state->objects[2].data.plane.dir = vec3_normalize(new_vec3(1., -1., 0.));
	state->objects[2].data.plane.pos = new_world_coord(100., -1., 0.);
	state->objects[2].color = new_color(0, 0, 255);
}

void	init(t_state *state, char *file)
{
	state = ft_memset(state, 0, sizeof(t_state));
	(void) file;
	//parse_scene(&state, file);
	init_dummy(state);
	init_dim(state);
	init_mlx(state);
	mlx_hook(state->win.ptr, KeyPress, KeyPressMask, handle_key_press, state);
	mlx_hook(state->win.ptr, KeyRelease, KeyReleaseMask,
		handle_key_release, state);
	mlx_loop_hook(state->mlx_ptr, main_loop, state);
	mlx_hook(state->win.ptr, DestroyNotify, StructureNotifyMask,
		call_exit, state);
}
