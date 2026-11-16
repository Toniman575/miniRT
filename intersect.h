/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:42:25 by asadik            #+#    #+#             */
/*   Updated: 2026/11/16 11:21:15 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "utils.h"

# define IN		true
# define OUT	false

# define CLIP_MAX 3
# define SHAPE_MAX 3

typedef struct s_sphere
{
	t_world_coord	center;
	double			radius;
}	t_sphere;

typedef struct s_plane
{
	t_world_coord		pos;
	t_vec3				dir;
}	t_plane;

typedef struct s_tube
{
	t_world_coord	center;
	t_vec3			dir;
	double			radius;
	//height will contribute to the clipping plane's pos = center + height/2 * ±dir
}	t_tube;

typedef union u_shape_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_tube		tube;
}	t_shape_data;

typedef enum e_shape_type
{
	SHAPE_NONE,
	SHAPE_SPHERE,
	SHAPE_PLANE,
	SHAPE_TUBE,
	SHAPE_COUNT
}	t_shape_type;

typedef enum e_object_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_COUNT
}	t_object_type;

typedef enum e_clip_type
{
	CT_NONE,
	CT_POS, 		// draw the side the normal points towards
	CT_NEG, 		// draw the side the normal doesnt point towards
	CT_COUNT
}	t_clip_type;

typedef struct s_clip
{
	t_clip_type	type; //if non zero used to control how the shape is used as a clip
	uint64_t	idx;  //idx of the shape we will use to clip with
}	t_clip;

typedef struct s_shape
{
	t_shape_type	type;
	t_shape_data	data;
	t_clip			clip[CLIP_MAX];
}	t_shape;

typedef struct s_object
{
	t_object_type	type;
	t_shape			shape[SHAPE_MAX];
	t_color			color;
	//t_transform	trans; //if we decide to add transformations to the individual objects
}	t_object;

typedef struct s_ray
{
	t_world_coord	origin;
	t_vec3			dir;
}	t_ray;

/// t is the length of the ray from its origin to hitpoint where
/// the intersection happens.
typedef struct s_intersection
{
	double			t;
	t_world_coord	hitpoint;
	t_shape			*shape;
	t_object		*object;
}	t_intersection;

#endif
