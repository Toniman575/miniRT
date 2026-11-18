/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:57:20 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:18:02 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "utils.h"

static double	light_intensity(t_state *state, t_option *option, t_ray ray)
{
	t_intersection	x;
	t_ray			ray_to_light;
	t_option		ray_x;
	double			len;
	double			intensity;

	x = option->value.intersection;
	ray_to_light.origin = x.hitpoint;
	ray_to_light.dir = vec3_normalize(vec3_sub(state->light.pos, x.hitpoint));
	ray_x = cast_ray(state, ray_to_light);
	len = vec3_len(vec3_sub(state->light.pos, x.hitpoint));
	if (ray_x.type == OT_INTERSECTION && (len > ray_x.value.intersection.t))
		return (state->ambient.brightness);
	intensity = vec3_dot(get_normal_facing_ray(x, ray), ray_to_light.dir);
	intensity *= state->light.brightness;
	intensity = fmax(0., intensity) + state->ambient.brightness;
	intensity = fmin(1., intensity);
	return (intensity);
}

t_xcolor	get_color_from_ray(t_state *state, t_option option, t_ray ray)
{
	t_color	color;
	double	intensity;

	ft_memset(&color, 0, sizeof(t_color));
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
