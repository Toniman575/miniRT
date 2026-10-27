/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:48:48 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 17:15:04 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "math.h"

typedef struct s_object t_object;

typedef struct s_light
{
	t_world_coord	pos;
	uint16_t			color[3];
}	t_light;

typedef struct s_sphere
{
	t_world_coord	center;
	double			diameter;
	uint16_t		color[3];
}	t_sphere;

typedef struct s_plane
{
	t_world_coord	pos;
	t_vec3			rot;
	uint16_t		color[3];
}	t_plane;

typedef struct s_cylinder
{
	t_world_coord	center;
	t_vec3			rot;
	double			diameter;
	double			height;
	uint16_t		color[3];
}	t_cylinder;

typedef union u_object_data
{
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_data;

typedef enum e_object_type
{
	OT_LIGHT,
	OT_SPHERE,
	OT_PLANE,
	OT_CYLINDER,
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_object_data	data;
}	t_object;

typedef struct s_intersection
{
	t_world_coord	pos;
	t_object		*object;
}	t_intersection;

t_intersection		*xchecker(t_object *object, t_ray *ray);

#endif