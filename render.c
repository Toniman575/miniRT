/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/10/31 16:13:46 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"
#include <math.h>
#include <stdint.h>

t_xcolor color_to_uint32(t_color c)
{
	return ((t_xcolor)c.a << 24)
		| ((t_xcolor)c.r << 16)
		| ((t_xcolor)c.g << 8)
		| (t_xcolor)c.b;
}

t_color	new_color(t_color_component red, t_color_component green, t_color_component blue)
{
	t_color color;

	color.a = 0;
	color.r = red;
	color.g = green;
	color.b = blue;
	return (color);
}

t_xcolor	get_color_from_ray(t_option intersection)
{
	if (intersection.type == OT_NONE)
		return (color_to_uint32(new_color(0, 0, 0)));
	else {
		return (intersection.value.intersection.object->color);
	}
}

t_option	cast_ray(t_state *state, t_ray ray)
{
	t_option	is;
	t_option	c_is;
	uint16_t	i;

	is.type = OT_NONE;
	c_is.type = OT_NONE;
	i = -1;
	while (++i < state->objects_n)
	{
		c_is = xchecker(&state->objects[i], &ray);
		if (is.type == OT_NONE && c_is.type != OT_NONE)
			is = c_is;
		else if (c_is.type != OT_NONE && is.type != OT_NONE && c_is.value.intersection.t
			< is.value.intersection.t)
			is = c_is;
	}
	return (is);
}

t_vec3 new_vec3(double x, double y, double z)
{
	t_vec3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	rotate_vec3(t_quaternion quat, t_vec3 vec)
{
	t_vec3	qv;
	t_vec3	t;

	qv = new_vec3(quat.x, quat.y, quat.z);
	t = vec3_mult(vec3_cross(qv, vec), 2.);
	return (vec3_add(vec3_add(vec, vec3_mult(t, quat.w)), vec3_cross(qv, t)));
}

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
		coord.y - half_height, -distance)));
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
	t_xcolor		color = 0x00FF0000;

	current.y = -1;
	while (++current.y < state->win.dim.height)
	{
		current.x = -1;
		while (++current.x < state->win.dim.width)
		{
			color = get_color_from_ray(cast_ray(state,
				viewport_ray(state, current)));
			put_pixel_to_buffer(state, current,
				mlx_get_color_value(state->mlx_ptr, color));
		}
	};
	//put_image_to_window(&state);
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, 0, 0);
}
