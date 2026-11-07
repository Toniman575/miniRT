/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:09:53 by asadik            #+#    #+#             */
/*   Updated: 2026/11/07 19:58:06 by asadik           ###   ########.fr       */
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
	t_object	*objects;
	uint64_t	idx;
	t_camera	cam = {
		.pos = {0., 0., 0.},
		.rotation = {1., 0., 0., 0.},
		.pan_speed = 0.1,
		.rot_speed = 0.05,
		.fov = 70.0
	};

	state->camera = cam;
	idx = get_idx_from_offset(&state->objects,
		arena_alloc(&state->objects, 3 * sizeof(t_object), _Alignof(t_object)));
	objects = (t_object *)state->objects.buf;
	objects[idx].type = OBJ_SPHERE;
	objects[idx].data.sphere.center = new_world_coord(-3., 0., -5.);
	objects[idx].data.sphere.radius = 1.;
	objects[idx].color = new_color(255, 0, 0);
	objects[idx + 1].type = OBJ_SPHERE;
	objects[idx + 1].data.sphere.center = new_world_coord(3., 0., -5.);
	objects[idx + 1].data.sphere.radius = 1.;
	objects[idx + 1].color = new_color(0, 255, 0);
	objects[idx + 2].type = OBJ_PLANE;
	objects[idx + 2].data.plane.dir = vec3_normalize(new_vec3(0., 1., 0.));
	objects[idx + 2].data.plane.pos = new_world_coord(0., -0.5, 0.);
	objects[idx + 2].color = new_color(0, 0, 255);
	state->light = (t_light){
		.pos = new_vec3(0., 0., -5.5),
		.brightness = 5.,
	};
	state->ambient.brightness = 0.1;
}

void	init_arena(t_state *state)
{
	state->objects = arena_init(ARENA_SIZE, sizeof(t_object));
	arena_hook_cleanup(&state->objects, (void (*)(void *))cleanup, state);
}

void	init(t_state *state, char *file)
{
	(void) file;

	ft_memset(state, 0, sizeof(t_state));
	init_arena(state);
	parse_scene(state, file);
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
