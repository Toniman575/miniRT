/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/10/28 00:09:39 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "utils.h"
#include "math.h"
#include <stdint.h>


/*diffuse_light()
{
	normal = calculate_normal(intersection);
}*/
/*
t_option	cast_ray(t_state *state, t_ray ray)
{
	t_option	is;
	t_option	c_is;
	uint16_t	i;

	is.type = NONE;
	c_is.type = NONE;
	i = -1;
	while (state->objects[++i])
	{
		c_is = xchecker(state->object[i], ray);
		if (world_distance(c_is.value.intersection.pos, ray.start)
			< world_distance(is.value.intersection.pos, ray.start))
			is = c_is;
	}
	return (is);
}

t_color	cast_ray(t_state *state, t_screen_coord *current)
{

	t_vec3		normal;
	
	while (state->objects[i])
	{
		current = xcheck(state->object[i]);
		if (intersection.pos > current_intersection.pos)
			intersection.pos = current_intersection.pos;
			intersection.object = &state->object[i];
	}
	if (intersection == Some)
	{
		i = 0;
		while (++i; state->lights[i])
			color += diffuse_light(intersection, state->lights[i]);
		color += ambient_light();
	}
	return (color);
}
*/
void	put_pixel_to_buffer(t_state *state, t_screen_coord sc, uint32_t color)
{
	size_t	idx;
	size_t	pixels_per_line;

	pixels_per_line = state->img.bytes_per_line * 8
		/ state->img.bits_per_pixel;
	idx = sc.y * pixels_per_line + sc.x;
	((unsigned int *)state->img.buf)[idx] = color;
}

void	draw(t_state *state)
{
	t_screen_coord	current;
	int32_t			color = 0x00FF0000;

	current.y = -1;
	while (++current.y < state->win.dim.height)
	{
		current.x = -1;
		while (++current.x < state->win.dim.width)
		{
			//color = cast_ray(state, &current);
			put_pixel_to_buffer(state, current,
				mlx_get_color_value(state->mlx_ptr, color));
		}
	};
	mlx_put_image_to_window(state->mlx_ptr, state->win.ptr,
		state->img.ptr, 0, 0);

	//put_image_to_window(&state);
}
