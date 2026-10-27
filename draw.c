/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:22:14 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 17:35:06 by asadik           ###   ########.fr       */
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
		if (world_distance(c_is.value.intersection.pos, ray.start) < world_distance(is.value.intersection.pos, ray.start))
			is = c_is;
	}
	return (c_is);
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

void	draw(t_state *state)
{
	t_screen_coord	current;

	while (++current.y < state.window.height)
	{
		while (++current.x < state.window.width)
			put_pixel_to_buffer(state, &current, cast_ray(state, &current));
	}
	put_image_to_window(&state);
}