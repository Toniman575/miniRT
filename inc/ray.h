/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:06:08 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:28:47 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "shape.h"

# define ROOTS_MAX 2

typedef struct s_ray
{
	t_world_coord	origin;
	t_vec3			dir;
}	t_ray;

typedef enum e_otype
{
	OT_NONE,
	OT_INTERSECTION,
	OT_LIN_ROOT,
	OT_QUAD_ROOT,
	OT_COUNT,
}	t_otype;

/// t is the length of the ray from its origin to hitpoint where
/// the intersection happens.
typedef struct s_intersection
{
	double			t;
	t_world_coord	hitpoint;
	t_shape			*shape;
	t_object		*object;
}	t_intersection;

typedef union u_ovalue
{
	t_intersection	intersection;
	double			t;
	double			ts[ROOTS_MAX];
}	t_ovalue;

typedef struct s_option
{
	t_otype		type;
	t_ovalue	value;
}	t_option;

typedef struct s_lin_eq
{
	double	a;
	double	b;
}	t_lin_eq;

typedef struct s_quad_eq
{
	double	a;
	double	b_half;
	double	c;
}	t_quad_eq;

t_intersection	new_intersection(t_object *object, t_shape *shape, double t,
					t_world_coord hitpoint);
t_option		intersect_object(t_object *object, t_ray *ray);
t_option		intersect_plane(t_object *object, t_shape *shape, t_ray *ray);
t_option		intersect_cylinder(t_object *object, t_shape *shape,
					t_ray *ray);
t_option		intersect_sphere(t_object *object, t_shape *shape, t_ray *ray);
t_lin_eq		build_lin_eq(t_shape *shape, t_ray *ray);
t_option		solve_lin_eq(t_lin_eq eq);
t_quad_eq		build_sphere_eq(t_shape *shape, t_ray *ray);
t_option		solve_quad_eq(t_quad_eq eq);
t_quad_eq		build_tube_eq(t_shape *shape, t_ray *ray);
t_vec3			get_normal_facing_ray(t_intersection x, t_ray ray);

#endif