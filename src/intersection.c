/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/10 12:46:24 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"

t_world_coord	get_ray_point(t_ray *ray, double t) {
	return (vec3_add(ray->origin, vec3_mult(ray->dir, t)));
}

///TODO:	Figure out which vars are needed for each object checker function
/// 		and write a seperate function for each.
///			we discard intersections behind the camera t < 0
///TODO:	stefan: are we checking close to 0, or negative?
///					for negatives we could use signbit() from math.h
t_option	xchecker(t_object *object, t_ray *ray)
{
	t_option	option;
	t_vec3		oc;

	option.type = OT_NONE;
	if (object->type == OBJ_SPHERE)
	{
		double	delta;
		double	sqrt_delta;
		double	b;
		double	c;
		double	t[2];
		oc = vec3_sub(ray->origin, object->data.sphere.center);
		b = 2. * vec3_dot(oc, ray->dir);
		c = vec3_dot(oc, oc)
			- ((object->data.sphere.radius) * (object->data.sphere.radius));
		delta = b * b - 4. * c;
		if (delta > EPSILON)
		{
			sqrt_delta = sqrt(delta);
			t[0] = (-b - sqrt_delta) / 2.;
			t[1] = (-b + sqrt_delta) / 2.;
			if (t[0] < EPSILON)
				t[0] = t[1];
			if (t[0] > EPSILON)
			{
				option.type = OT_INTERSECTION;
				option.value.intersection.object = object;
				option.value.intersection.t = t[0];
				option.value.intersection.hitpoint = get_ray_point(ray, t[0]);
			}
		}
	}
	else if (object->type == OBJ_PLANE)
	{
		double	d;
		double	t;
		d = vec3_dot(ray->dir, object->data.plane.dir);
		if (fabs(d) > EPSILON)
		{
			t = vec3_dot(vec3_sub(object->data.plane.pos, ray->origin),
				object->data.plane.dir) / d;
			if (t > EPSILON)
			{
				option.type = OT_INTERSECTION;
				option.value.intersection.object = object;
				option.value.intersection.t = t;
				option.value.intersection.hitpoint = get_ray_point(ray, t);
			}
		}
	}
	return (option);
}
