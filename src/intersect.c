/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/16 15:08:59 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"

t_world_coord	get_ray_point(t_ray *ray, double t) {
	return (vec3_add(ray->origin, vec3_mult(ray->dir, t)));
}


	// ft_memset(&ret, 0, sizeof(t_option));
	// eq = build_lin_eq(object, ray);
	// root = solve_lin_eq(eq);


// t_option	intersect_sphere(t_object *object, t_ray *ray)
// {
// 	t_quad_eq	eq;
// 	t_option	res;
// 	t_option	option;

// 	eq = build_quad_eq(object, ray);
// 	t = solve_quad_eq(eq);

// 	t_vec3	oc;
// 	double	delta;
// 	double	sqrt_delta;
// 	double	b;
// 	double	c;
// 	oc = vec3_sub(ray->origin, object->shape[0].data.sphere.center);
// 	b = 2. * vec3_dot(oc, ray->dir);
// 	c = vec3_dot(oc, oc)
// 		- ((object->shape[0].data.sphere.radius) * (object->shape[0].data.sphere.radius));
// 	delta = b * b - 4. * c;
// 	if (delta > EPSILON)
// 	{
// 		sqrt_delta = sqrt(delta);
// 		t[0] = (-b - sqrt_delta) / 2.;
// 		t[1] = (-b + sqrt_delta) / 2.;
// 		if (t[0] < EPSILON)
// 			t[0] = t[1];
// 		if (t[0] > EPSILON)
// 		{
// 			option.type = OT_INTERSECTION;
// 			option.value.intersection.object = object;
// 			option.value.intersection.t = t[0];
// 			option.value.intersection.hitpoint = get_ray_point(ray, t[0]);
// 		}
// 	}
// }

t_lin_eq	build_lin_eq(t_object *object, t_ray *ray)
{
	t_lin_eq	eq;

	eq.a = vec3_dot(ray->dir, object->shape->data.plane.dir);
	eq.b = vec3_dot(object->shape->data.plane.dir,
			vec3_sub(ray->origin, object->shape->data.plane.pos));
	return (eq);
}

t_option	solve_lin_eq(t_lin_eq eq)
{
	t_option	ret;

	ft_memset(&ret, 0, sizeof(t_option));
	if (eq.a > -EPSILON && eq.a < EPSILON)
	{
		ret.type = OT_DOUBLE;
		ret.value.t = -eq.b/eq.a;
	}
	return (ret);
}

t_option	intersect_plane(t_object *object, t_ray *ray)
{
	t_lin_eq	eq;
	t_option	root;
	t_option	ret;

	ft_memset(&ret, 0, sizeof(t_option));
	eq = build_lin_eq(object, ray);
	root = solve_lin_eq(eq);
	if (root.type == OT_DOUBLE && root.value.t > EPSILON)
	{
		ret.type = OT_INTERSECTION;
		ret.value.intersection.t = root.value.t;
		ret.value.intersection.object = object;
		ret.value.intersection.shape = object->shape;
	}
	return (ret);
}

//cylinder
	// {
	// 	t_vec3	oc;
	// 	t_vec3	nxa;
	// 	t_vec3	bxa;
	// 	double	bnxa;
	// 	double	b_neg;
	// 	double	a_double;
	// 	double	delta;
	// 	double	sqrt_delta;
	// 	double	t[2];

	// 	oc = vec3_sub(object->data.cylinder.center, ray->origin);
	// 	nxa = vec3_cross(ray->dir, object->data.cylinder.dir);
	// 	bxa = vec3_cross(oc, object->data.cylinder.dir);
	// 	bnxa = vec3_dot(oc, nxa);
	// 	b_neg = vec3_dot(nxa, bxa);
	// 	a_double = vec3_dot(nxa, nxa);
	// 	delta = a_double * object->data.cylinder.radius * object->data.cylinder.radius - bnxa * bnxa;
	// 	sqrt_delta = sqrt(delta);
	// 	if (delta > EPSILON)
	// 	{
	// 		t[0] = (b_neg - sqrt_delta) / a_double;
	// 		t[1] = (b_neg + sqrt_delta) / a_double;
	// 		// t_world_coord a = vec3_add(ray->origin, vec3_mult(ray->dir, t[0]));
	// 		// t_world_coord b = vec3_add(ray->origin, vec3_mult(ray->dir, t[1]));
	// 		// t_world_coord c = vec3_add(ray->origin, vec3_mult(ray->dir, (t[0] + t[1]) / 2.));
	// 		// t_vec3 d = vec3_sub(c, a);
	// 		if (t[0] < EPSILON)
	// 		{
	// 			t[0] = t[1];
	// 			// d = vec3_sub(c, b);
	// 		}
	// 		if (t[0] > EPSILON)
	// 		{
	// 			double dot = vec3_dot(vec3_sub(object->data.cylinder.center, get_ray_point(ray, t[0])), object->data.cylinder.dir);
	// 			if (dot > -(object->data.cylinder.height / 2.) && dot < object->data.cylinder.height / 2.)
	// 			{
	// 				option.type = OT_INTERSECTION;
	// 				option.value.intersection.object = object;
	// 				option.value.intersection.t = t[0];
	// 				option.value.intersection.hitpoint = get_ray_point(ray, t[0]);
	// 			}
	// 		}
	// 	}
	// }

t_option	xchecker(t_object *object, t_ray *ray)
{
	t_option	option;

	option.type = OT_NONE;
	//if (object->type == OBJ_SPHERE)
		//intersect_sphere(object, ray);
	if (object->type == OBJ_PLANE)
		intersect_plane(object, ray);
	//else if (object->type == OBJ_CYLINDER)
		//intersect_cylinder(object, ray);
	return (option);
}

