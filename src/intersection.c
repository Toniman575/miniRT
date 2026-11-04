/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/04 14:36:16 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"
#include <math.h>

/// TODO:	Figure out which vars are needed for each object checker function
/// 		and write a seperate function for each.
t_option	xchecker(t_object *object, t_ray *ray)
{
	t_option	option;
	t_vec3		oc;

	option.type = OT_NONE;
	if (object->type == OBJ_SPHERE)
	{
		oc = vec3_sub(ray->origin, object->data.sphere.center);
		double a = vec3_dot(ray->dir, ray->dir);
		double b = 2. * vec3_dot(oc, ray->dir);
		double c = vec3_dot(oc, oc)
			- ((object->data.sphere.radius)
			* (object->data.sphere.radius));
		double delta = b * b - 4. * a * c;
		if (islessequal(delta, 0.))
			option.type = OT_NONE;
		else {
			double sqrt_delta = sqrt(delta);
			double t0 = (-b - sqrt_delta) / (2. * a);
			double t1 = (-b + sqrt_delta) / (2. * a);
			if (islessequal(t0, 0.))
				t0 = t1;
			if (islessequal(t0, 0.))
				option.type = OT_NONE;
			else
			{
				option.type = OT_INTERSECTION;
				option.value.intersection.object = object;
				option.value.intersection.t = t0;
			}
		}
	}
	else if (object->type == OBJ_PLANE)
	{
		double d = vec3_dot(ray->dir, object->data.plane.dir);
		if (fabs(d) < 0.01)
			option.type = OT_NONE;
		else
		{
			double t = vec3_dot(vec3_sub(object->data.plane.pos, ray->origin),
				object->data.plane.dir) / d;
			if (islessequal(t, 0.))
				option.type = OT_NONE;
			else
			{
				option.type = OT_INTERSECTION;
				option.value.intersection.object = object;
				option.value.intersection.t = t;
			}
		}
	}
	else
		option.type = OT_NONE;
	return (option);
}
