/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:41:10 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:20:41 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "config.h"
#include "libft.h"
#include "ray.h"

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
		ret.value.t = -eq.b / eq.a;
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
