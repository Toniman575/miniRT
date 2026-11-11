/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/11 16:17:19 by sancuta          ###   ########.fr       */
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
		// d == 0 means they are parallel and don't intersect
		d = vec3_dot(ray->dir, object->data.plane.dir);
		if (fabs(d) > EPSILON)
		{
			// t <= 0 means there intersection is behind our ray origin, the '/d' is normalization
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
	else if (object->type == OBJ_CYLINDER)
	{
		t_vec3	oc;
		t_vec3	nxa;
		t_vec3	bxa;
		double	bnxa;
		double	b_neg;
		double	a_double;
		double	delta;
		double	sqrt_delta;
		double	t[2];

		oc = vec3_sub(object->data.cylinder.center, ray->origin);
		nxa = vec3_cross(ray->dir, object->data.cylinder.dir);
		bxa = vec3_cross(oc, object->data.cylinder.dir);
		bnxa = vec3_dot(oc, nxa);
		b_neg = vec3_dot(nxa, bxa);
		a_double = vec3_dot(nxa, nxa);
		delta = a_double * object->data.cylinder.radius * object->data.cylinder.radius - bnxa * bnxa;
		sqrt_delta = sqrt(delta);
		if (delta > EPSILON)
		{
			t[0] = (b_neg - sqrt_delta) / a_double;
			t[1] = (b_neg + sqrt_delta) / a_double;
			if (t[0] < EPSILON)
				t[0] = t[1];
			if (t[0] > EPSILON)
			{
				option.type = OT_INTERSECTION;
				option.value.intersection.object = object;
				option.value.intersection.t = t[0];
				option.value.intersection.hitpoint = get_ray_point(ray, t[0]);
//				t_ax = vec3_dot(object->data.cylinder.dir, vec3_sub(vec_mult(ray->dir, t[0]), oc));
//				if (t > EPSILON && t < object->data.cylinder.height && t )

			}

		}
	}
	return (option);
}
