/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/11/07 19:55:47 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "vector.h"
#include <math.h>
#include <stdint.h>

t_vec3 get_normal(t_intersection intersection)
{
	if (intersection.object->type == OBJ_SPHERE)
		return (vec3_normalize(vec3_sub(intersection.hitpoint, intersection.object->data.sphere.center)));
	else if (intersection.object->type == OBJ_PLANE)
		return (intersection.object->data.plane.dir);
	else 
		return (new_vec3(0., 0., 0.));
}

t_xcolor	get_color_from_ray(t_state *state, t_option intersection)
{
	t_color color;
	t_intersection x;

	ft_memset(&color, 0, sizeof(t_color));
	if (intersection.type == OT_NONE)
		return (0);
	else
	{
		x = intersection.value.intersection;
		color = intersection.value.intersection.object->color;
		t_vec3 normal = get_normal(x);
		double intensity = fmin(1., fmax(0., vec3_dot(normal, 
			vec3_sub(state->light.pos, x.hitpoint))) + state->ambient.brightness);
		return (x_color_from_color(
			new_color(color.r * intensity, color.g * intensity, color.b * intensity)));
	}
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
		c_is = xchecker(&objects[i], &ray);
		if (is.type == OT_NONE && c_is.type != OT_NONE)
			is = c_is;
		else if (c_is.type != OT_NONE && is.type != OT_NONE
			&& c_is.value.intersection.t < is.value.intersection.t)
			is = c_is;
	}
	return (is);
}

/// TODO: Optimize: Move rotation to be pre computed in the camerastruct and not at each ray.
t_ray	viewport_ray(t_state *state, t_screen_coord coord)
{
	t_ray		ray;
	double		distance;
	double		half_width;
	double		half_height;
	double		fov_rad;

	fov_rad = state->camera.fov * M_PI / 180.;
	half_width = state->win.dim.width / 2.;
	half_height = state->win.dim.height / 2.;
	distance = half_width / (tan(fov_rad / 2.));
	ray.origin = state->camera.pos;
	ray.dir = rotate_vec3(state->camera.rotation,
		vec3_normalize(new_vec3(coord.x - half_width,
			half_height - coord.y, -distance)));
	return (ray);
}

void	put_pixel_to_buffer(t_state *state, t_screen_coord sc, uint32_t color)
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

	current.y = -1;
	while (++current.y < state->win.dim.height)
	{
		current.x = -1;
		while (++current.x < state->win.dim.width)
		{
			color = get_color_from_ray(state, cast_ray(state,
						viewport_ray(state, current)));
			put_pixel_to_buffer(state, current,
				mlx_get_color_value(state->mlx_ptr, color));
		}
	}
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, 0, 0);
}
