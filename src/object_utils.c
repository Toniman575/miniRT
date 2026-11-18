/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:54:43 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:22:34 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "ray.h"
#include "vector.h"

static t_vec3	get_normal(t_intersection x)
{
	t_vec3	v;
	t_vec3	axial;
	t_vec3	radial;

	if (x.shape->type == SHAPE_PLANE)
		return (x.shape->data.plane.dir);
	else if (x.shape->type == SHAPE_SPHERE)
		return (vec3_normalize(vec3_sub(x.hitpoint,
					x.shape->data.sphere.center)));
	else if (x.shape->type == SHAPE_TUBE)
	{
		v = vec3_sub(x.hitpoint,
				x.object->shape[0].data.tube.center);
		axial = vec3_mult(x.object->shape[0].data.tube.dir,
				vec3_dot(v, x.object->shape[0].data.tube.dir));
		radial = vec3_sub(v, axial);
		return (vec3_normalize(radial));
	}
	else
		return (new_vec3(0., 0., 0.));
}

t_vec3	get_normal_facing_ray(t_intersection x, t_ray ray)
{
	t_vec3	normal;

	normal = get_normal(x);
	if (vec3_dot(normal, ray.dir) > EPSILON)
		normal = vec3_mult(normal, -1.);
	return (normal);
}
