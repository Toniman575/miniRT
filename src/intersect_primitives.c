/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_primitives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:34:23 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:20:12 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "config.h"
#include "libft.h"
#include "ray.h"
#include "vector.h"

static t_world_coord	get_ray_point(t_ray *ray, double t)
{
	return (vec3_add(ray->origin, vec3_mult(ray->dir, t)));
}

static t_option	intersect_tube(t_object *object, t_shape *shape, t_ray *ray)
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
			res.value.intersection
				= new_intersection(object, shape, root.value.ts[i], hitpoint);
			break ;
		}
	}
	return (res);
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
		ret.value.intersection
			= new_intersection(object, shape, root.value.t, hitpoint);
	}
	return (ret);
}

t_option	intersect_cylinder(t_object *object, t_shape *shape, t_ray *ray)
{
	t_option	is[3];
	size_t		i;

	is[0] = intersect_tube(object, &shape[0], ray);
	is[1] = intersect_plane(object, &shape[1], ray);
	is[2] = intersect_plane(object, &shape[2], ray);
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
			res.value.intersection
				= new_intersection(object, shape, root.value.ts[i], hitpoint);
			break ;
		}
	}
	return (res);
}
