/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:09:53 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 15:20:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <X11/X.h>

#include "config.h"
#include "state.h"
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

	state->camera = (t_camera){
		.pos = {0., 0., 10.},
		.rotation = {1., 0., 0., 0.},
		.pan_speed = 0.1,
		.rot_speed = 0.05,
		.fov = 100.0
	};
	state->redraw = true;
	state->light = (t_light){
		.pos = new_vec3(3., 0., 4.),
		.brightness = 1.,
	};
	state->ambient.brightness = .25;
	idx = get_idx_from_offset(&state->objects,
		arena_alloc(&state->objects, 7 * sizeof(t_object), _Alignof(t_object)));
	objects = (t_object *)state->objects.buf;
	objects[idx].type = OBJ_SPHERE;
	objects[idx].shape[0].type = SHAPE_SPHERE;
	objects[idx].shape[0].data.sphere.center = new_world_coord(-3., 0., 5.);
	objects[idx].shape[0].data.sphere.radius = 1.;
	objects[idx].color = new_color(255, 0, 0);
	objects[idx + 1].type = OBJ_SPHERE;
	objects[idx + 1].shape[0].type = SHAPE_SPHERE;
	objects[idx + 1].shape[0].data.sphere.center = new_world_coord(3., 0., 5.);
	objects[idx + 1].shape[0].data.sphere.radius = 1.;
	objects[idx + 1].shape[0].clip[0].type = CT_POS;
	objects[idx + 1].shape[0].clip[0].shape = &objects[idx + 6].shape[0];
	objects[idx + 1].shape[0].clip[0].shape->type = SHAPE_PLANE;
	objects[idx + 1].shape[0].clip[0].shape->data.plane.pos = new_world_coord(3., 0., 5.5);;
	objects[idx + 1].shape[0].clip[0].shape->data.plane.dir = vec3_normalize(new_world_coord(1., 0., 0.));
	objects[idx + 1].color = new_color(0, 255, 0);
	objects[idx + 2].type = OBJ_SPHERE;
	objects[idx + 2].shape[0].type = SHAPE_SPHERE;
	objects[idx + 2].shape[0].data.sphere.center = new_world_coord(0., 0., 0.);
	objects[idx + 2].shape[0].data.sphere.radius = 50.;
	objects[idx + 2].color = new_color(255, 165, 0);
	objects[idx + 3].type = OBJ_PLANE;
	objects[idx + 3].shape[0].type = SHAPE_PLANE;
	objects[idx + 3].shape[0].data.plane.dir = vec3_normalize(new_vec3(0., 1., 0.));
	objects[idx + 3].shape[0].data.plane.pos = new_world_coord(0., -3., 0.);
	objects[idx + 3].color = new_color(0, 0, 255);
	objects[idx + 4].type = OBJ_PLANE;
	objects[idx + 4].shape[0].type = SHAPE_PLANE;
	objects[idx + 4].shape[0].data.plane.dir = vec3_normalize(new_vec3(0., -1., 0.));
	objects[idx + 4].shape[0].data.plane.pos = new_world_coord(0., 3., 0.);
	objects[idx + 4].color = new_color(0, 0, 255);
	double	height;
	height = 3.;
	objects[idx + 5].type = OBJ_CYLINDER;
	objects[idx + 5].shape[0].type = SHAPE_TUBE;
	objects[idx + 5].shape[0].data.tube.center = new_world_coord(0., 0., -6.);
	objects[idx + 5].shape[0].data.tube.dir = vec3_normalize(new_vec3(1., 1., 1.));
	objects[idx + 5].shape[0].data.tube.radius = 2.;
	objects[idx + 5].shape[0].clip[0].type = CT_NEG;
	objects[idx + 5].shape[0].clip[0].shape = &objects[idx + 5].shape[1];
	objects[idx + 5].shape[0].clip[0].shape->type = SHAPE_PLANE;
	objects[idx + 5].shape[0].clip[0].shape->data.plane.pos
		= vec3_add(objects[idx + 5].shape[0].data.tube.center,
		vec3_mult(objects[idx + 5].shape[0].data.tube.dir,
		height / 2.));
	objects[idx + 5].shape[0].clip[0].shape->data.plane.dir
		= objects[idx + 5].shape[0].data.tube.dir;
	objects[idx + 5].shape[0].clip[1].type = CT_POS;
	objects[idx + 5].shape[0].clip[1].shape = &objects[idx + 5].shape[2];
	objects[idx + 5].shape[0].clip[1].shape->type = SHAPE_PLANE;
	objects[idx + 5].shape[0].clip[1].shape->data.plane.pos
		= vec3_add(objects[idx + 5].shape[0].data.tube.center,
		vec3_mult(objects[idx + 5].shape[0].data.tube.dir,
		-height / 2.));
	objects[idx + 5].shape[0].clip[1].shape->data.plane.dir
		= objects[idx + 5].shape[0].data.tube.dir;
	objects[idx + 5].shape[1].clip[0].type = CT_POS;
	objects[idx + 5].shape[1].clip[0].shape = &objects[idx + 5].shape[0];
	objects[idx + 5].shape[2].clip[0].type = CT_POS;
	objects[idx + 5].shape[2].clip[0].shape = &objects[idx + 5].shape[0];
	objects[idx + 5].color = new_color(165, 165, 255);
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
	update_view(state);
	init_mlx(state);
	mlx_hook(state->win.ptr, KeyPress, KeyPressMask, handle_key_press, state);
	mlx_hook(state->win.ptr, KeyRelease, KeyReleaseMask,
		handle_key_release, state);
	mlx_loop_hook(state->mlx_ptr, main_loop, state);
	mlx_hook(state->win.ptr, DestroyNotify, StructureNotifyMask,
		call_exit, state);
}
