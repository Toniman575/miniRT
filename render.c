/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/10/29 17:04:52 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>
#include <stdint.h>

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
		if (c_is.type != OT_NONE && world_distance(c_is.value.intersection.pos, ray.origin)
			< world_distance(is.value.intersection.pos, ray.origin))
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

t_ray	viewport_ray(t_state *state, t_screen_coord coord)
{
	t_ray		ray;
	double		distance;
	double		half_width;
	double		half_height;

	half_width = state->win.dim.width / 2.;
	half_height = state->win.dim.height / 2.;
	distance = half_width / (tan((double)state->camera.fov / 2.));
	ray.origin = state->camera.pos;
	ray.dir = apply_rotation(state->camera.rotation,
		normalize_vec3(new_vec3((int16_t)coord.x - half_width,
		(int16_t)coord.y - half_height, -distance)));
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
	int32_t			color = 0x00FF0000;

	current.y = -1;
	while (++current.y < state->win.dim.height)
	{
		current.x = -1;
		while (++current.x < state->win.dim.width)
		{
			color = get_color_from_ray(cast_ray(state, viewport_ray(state, current)));
			put_pixel_to_buffer(state, current,
				mlx_get_color_value(state->mlx_ptr, color));
		}
	};
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, 0, 0);

	//put_image_to_window(&state);
}
