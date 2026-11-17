/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/17 03:24:09 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"

t_world_coord	get_ray_point(t_ray *ray, double t) {
	return (vec3_add(ray->origin, vec3_mult(ray->dir, t)));
}

t_lin_eq	build_lin_eq(t_shape *shape, t_ray *ray)
{
	t_lin_eq	eq;

	eq.a = vec3_dot(ray->dir, shape->data.plane.dir);
	eq.b = vec3_dot(shape->data.plane.dir,
			vec3_sub(ray->origin, shape->data.plane.pos));
	return (eq);
}

t_option	solve_lin_eq(t_lin_eq eq)
{
	t_option	ret;

	ft_memset(&ret, 0, sizeof(t_option));
	if (eq.a < -EPSILON || eq.a > EPSILON)
	{
		ret.type = OT_LIN_ROOT;
		ret.value.t = -eq.b/eq.a;
	}
	return (ret);
}

t_option	intersect_plane(t_object *object, t_shape *shape, t_ray *ray)
{
	t_lin_eq		eq;
	t_option		root;
	t_option		ret;
	t_world_coord	hitpoint;

	ft_memset(&ret, 0, sizeof(t_option));
	eq = build_lin_eq(shape, ray);
	root = solve_lin_eq(eq);
	if (root.type != OT_LIN_ROOT)
		return (ret);
	hitpoint = get_ray_point(ray, root.value.t);
	if (root.value.t > EPSILON && is_clip(shape, hitpoint))
	{
		ret.type = OT_INTERSECTION;
		ret.value.intersection.object = object;
		ret.value.intersection.shape = shape;
		ret.value.intersection.t = root.value.t;
		ret.value.intersection.hitpoint = hitpoint;
	}
	return (ret);
}

// oc: the vector from ray origin to object center
t_quad_eq	build_sphere_eq(t_shape *shape, t_ray *ray)
{
	t_quad_eq	eq;
	t_vec3		oc;

	oc = vec3_sub(ray->origin, shape->data.sphere.center);
	eq.a = 1.;
	eq.b_half = vec3_dot(ray->dir, oc);
	eq.c = vec3_len_pow2(oc) - pow(shape->data.sphere.radius, 2);
	return (eq);
}

t_option	solve_quad_eq(t_quad_eq eq)
{
	t_option	root;
	double		delta_reduced;

	ft_memset(&root, 0, sizeof(t_option));
	if (-EPSILON < eq.a && eq.a < EPSILON)
		return (root);
	delta_reduced = eq.b_half * eq.b_half - eq.a * eq.c;
	if (delta_reduced > EPSILON)
	{
		root.type = OT_QUAD_ROOT;
		root.value.ts[0] = (-eq.b_half - sqrt(delta_reduced)) / eq.a;
		root.value.ts[1] = (-eq.b_half + sqrt(delta_reduced)) / eq.a;
	}
	return (root);
}

t_option	intersect_sphere(t_object *object, t_shape *shape, t_ray *ray)
{
	t_quad_eq		eq;
	t_option		root;
	t_option		res;
	t_world_coord	hitpoint;
	size_t			i;


	ft_memset(&res, 0, sizeof(t_option));
	eq = build_sphere_eq(shape, ray);
	root = solve_quad_eq(eq);
	if (root.type != OT_QUAD_ROOT)
		return (res);
	i = -1;
	while (++i < ROOTS_MAX)
	{
		hitpoint = get_ray_point(ray, root.value.ts[i]);
		if (root.value.ts[i] > EPSILON && is_clip(shape, hitpoint))
		{
			res.type = OT_INTERSECTION;
			res.value.intersection.object = object;
			res.value.intersection.shape = shape;
			res.value.intersection.t = root.value.ts[i];
			res.value.intersection.hitpoint = hitpoint;
			break ;
		}
	}
	return (res);
}

t_quad_eq	build_tube_eq(t_shape *shape, t_ray *ray)
{
	t_quad_eq	eq;
	t_vec3		oc;
	t_vec3		nxa;
	t_vec3		bxa;

	oc = vec3_sub(ray->origin, shape->data.tube.center);
	nxa = vec3_cross(ray->dir, shape->data.tube.dir);
	bxa = vec3_cross(oc, shape->data.tube.dir);
	eq.a = vec3_dot(nxa, nxa);
	eq.b_half = vec3_dot(nxa, bxa);
	eq.c = vec3_dot(bxa, bxa) - pow(shape->data.tube.radius, 2);
	return (eq);
}

t_option	intersect_tube(t_object *object, t_shape *shape, t_ray *ray)
{
	t_quad_eq		eq;
	t_option		root;
	t_option		res;
	t_world_coord	hitpoint;
	size_t			i;


	ft_memset(&res, 0, sizeof(t_option));
	eq = build_tube_eq(shape, ray);
	root = solve_quad_eq(eq);
	if (root.type != OT_QUAD_ROOT)
		return (res);
	i = -1;
	while (++i < ROOTS_MAX)
	{
		hitpoint = get_ray_point(ray, root.value.ts[i]);
		if (root.value.ts[i] > EPSILON && is_clip(shape, hitpoint))
		{
			res.type = OT_INTERSECTION;
			res.value.intersection.object = object;
			res.value.intersection.shape = shape;
			res.value.intersection.t = root.value.ts[i];
			res.value.intersection.hitpoint = hitpoint;
			break ;
		}
	}
	return (res);
}

t_option	intersect_cylinder(t_object *object, t_shape *shape, t_ray *ray)
{
	t_option	is[3];
	size_t		i;

	is[0] = intersect_tube(object, &shape[0], ray);
	is[1] = intersect_plane(object, &shape[1], ray);	//TOP
	is[2] = intersect_plane(object, &shape[2], ray);	//BOTTOM
	i = 0;
	while (++i < SHAPES_MAX)
	{
		if (is[i].type == OT_INTERSECTION)
		{
			if (is[0].type != OT_INTERSECTION)
				is[0] = is[i];
			else if (is[0].type == OT_INTERSECTION
				&& is[i].value.intersection.t < is[0].value.intersection.t)
				is[0] = is[i];
		}
	}
	return (is[0]);
}

t_option	intersect_object(t_object *object, t_ray *ray)
{
	t_option	option;

	option.type = OT_NONE;
	if (object->type == OBJ_PLANE)
		option = intersect_plane(object, object->shape, ray);
	else if (object->type == OBJ_SPHERE)
		option = intersect_sphere(object, object->shape, ray);
	else if (object->type == OBJ_CYLINDER)
		option = intersect_cylinder(object, object->shape, ray);
	return (option);
}
