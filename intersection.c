/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/31 16:02:54 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"
#include <math.h>

/// TODO:	Figure out which variables are needed for each object checker function
/// 		and write a seperate function for each.
t_option	xchecker(t_object *object, t_ray *ray)
{
	t_option	option;
	t_vec3 		oc;

	if (object->type == OBJ_SPHERE)
	{
		oc = vec3_sub(ray->origin, object->data.sphere.center);
		double a = vec3_dot(ray->dir, ray->dir);
		double b = 2. * vec3_dot(oc, ray->dir);
		double c = vec3_dot(oc, oc) -
			((object->data.sphere.diameter / 2.) * (object->data.sphere.diameter / 2.));
		double d = b * b - 4 * a * c;
		if (islessequal(d, 0.))
			option.type = OT_NONE;
		else {
			double sd = sqrt(d);
			double t0 = (-b - sd) / (2. * a);
			double t1 = (-b + sd) / (2. * a);
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
	else
		option.type = OT_NONE;
	return (option);
}

