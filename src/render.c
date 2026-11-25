/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 16:43:00 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>

#include "ray.h"
#include "scene.h"
#include "state.h"
#include "utils.h"
#include "vector.h"

void	update_view(t_state *state)
{
	t_camera	*c;
	double		step;
	t_vec3		right;
	t_vec3		up;
	t_vec3		forward;

	c = &state->camera;
	step = 2. * tan(c->fov * M_PI / 360.) / state->img.dim.width;
	right = vec3_rot(c->rotation, new_vec3(1., 0., 0.));
	up = vec3_rot(c->rotation, new_vec3(0., 1., 0.));
	forward = vec3_rot(c->rotation, new_vec3(0., 0., -1.));
	c->viewport.sx = vec3_mult(right, step);
	c->viewport.sy = vec3_mult(up, -step);
	c->viewport.top_left = vec3_add(forward,
			vec3_add(vec3_mult(c->viewport.sx, 0.5 - state->img.dim.width / 2.),
				vec3_mult(c->viewport.sy, 0.5 - state->img.dim.height / 2.)));
}

t_option	cast_ray(t_state *state, t_ray ray)
{
	t_option	is;
	t_option	c_is;
	uint16_t	i;
	uint16_t	max_objects;
	t_object	*objects;

	objects = (t_object *)(state->objects.buf);
	max_objects = get_idx_from_offset(&state->objects, state->objects.offset);
	is.type = OT_NONE;
	c_is.type = OT_NONE;
	i = 0;
	while (++i < max_objects)
	{
		c_is = intersect_object(&objects[i], &ray);
		if (is.type != OT_INTERSECTION && c_is.type == OT_INTERSECTION)
			is = c_is;
		else if (c_is.type == OT_INTERSECTION && is.type == OT_INTERSECTION
			&& c_is.value.intersection.t < is.value.intersection.t)
			is = c_is;
	}
	return (is);
}

static t_ray	viewport_ray(t_camera *camera, t_coord2d x, t_vec3 row)
{
	t_ray		ray;

	ray.origin = camera->pos;
	ray.dir = vec3_normalize(vec3_add(row, vec3_mult(camera->viewport.sx, x)));
	return (ray);
}

static void	put_pixel_to_buffer(t_state *state,
	t_screen_coord sc, uint32_t color)
{
	size_t	idx;
	size_t	pixels_per_line;

	pixels_per_line = state->img.bytes_per_line * 8
		/ state->img.bits_per_pixel;
	idx = sc.y * pixels_per_line + sc.x;
	((unsigned int *)state->img.buf)[idx] = color;
}

void	render(t_state *state)
{
	t_screen_coord	current;
	t_xcolor		color;
	t_option		option;
	t_ray			ray;
	t_vec3			row;

	update_view(state);
	current.y = -1;
	while (++current.y < state->img.dim.height)
	{
		row = vec3_add(state->camera.viewport.top_left, vec3_mult(state->camera.viewport.sy, current.y));
		current.x = -1;
		while (++current.x < state->img.dim.width)
		{
			ray = viewport_ray(&state->camera, current.x, row);
			option = cast_ray(state, ray);
			color = get_color_from_ray(state, option, ray);
			put_pixel_to_buffer(state, current,
				mlx_get_color_value(state->mlx_ptr, color));
		}
	}
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, 0, 0);
}
