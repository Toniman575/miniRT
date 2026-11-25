/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:57:20 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 16:16:41 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "utils.h"
#include "config.h"

static bool	is_occluded(t_state *state, t_ray ray, double max_t)
{
	t_object	*objects;
	t_option	hit;
	uint16_t	i;
	uint16_t	max_objects;

	objects = (t_object *)state->objects.buf;
	max_objects = get_idx_from_offset(&state->objects, state->objects.offset);
	i = 0;
	while (++i < max_objects)
	{
		hit = intersect_object(&objects[i], &ray);
		if (hit.type == OT_INTERSECTION
			&& hit.value.intersection.t < max_t - EPSILON)
			return (true);
	}
	return (false);
}

static double	light_intensity(t_state *state, t_option *option, t_ray ray)
{
	t_intersection	x;
	t_ray			ray_to_light;
	double			len;
	double			intensity;

	x = option->value.intersection;
	ray_to_light.origin = x.hitpoint;
	ray_to_light.dir = vec3_sub(state->light.pos, x.hitpoint);
	len = vec3_len(ray_to_light.dir);
	ray_to_light.dir = vec3_normalize(ray_to_light.dir);
	intensity = vec3_dot(get_normal_facing_ray(x, ray), ray_to_light.dir);
	if (intensity <= 0)
		return (state->ambient.brightness);
	if (is_occluded(state, ray_to_light, len))
		return (state->ambient.brightness);
	intensity *= state->light.brightness;
	intensity = fmax(0., intensity) + state->ambient.brightness;
	intensity = fmin(1., intensity);
	return (intensity);
}

t_xcolor	get_color_from_ray(t_state *state, t_option option, t_ray ray)
{
	t_color	color;
	double	intensity;

	if (option.type == OT_NONE)
		return (0);
	color = option.value.intersection.object->color;
	intensity = light_intensity(state, &option, ray);
	return (x_color_from_color(
			new_color(
				color.r * intensity,
				color.g * intensity,
				color.b * intensity)));
}
