/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:03:29 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:40:55 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include <stdbool.h>
# include <stdint.h>
# include "vector.h"
# include "color.h"

# define CLIP_MAX 3
# define SHAPES_MAX 3

typedef struct s_plane
{
	t_world_coord		pos;
	t_vec3				dir;
}	t_plane;

typedef struct s_sphere
{
	t_world_coord	center;
	double			radius;
}	t_sphere;

//height will contribute to the clipping plane's pos = center + dir * ±height/2
typedef struct s_tube
{
	t_world_coord	center;
	t_vec3			dir;
	double			radius;
}	t_tube;

typedef union u_shape_data
{
	t_plane		plane;
	t_sphere	sphere;
	t_tube		tube;
}	t_shape_data;

typedef enum e_shape_type
{
	SHAPE_NONE,
	SHAPE_CIRCLE,
	SHAPE_PLANE,
	SHAPE_SPHERE,
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

//CT_POS draw the side the normal points towards
//CT_NEG draw the side the normal doesnt point towards
typedef enum e_clip_type
{
	CT_NONE,
	CT_POS,
	CT_NEG,
	CT_COUNT
}	t_clip_type;

typedef struct s_shape	t_shape;

//type: if non zero used to control how the shape is used as a clip
//obj_idx: idx of the object we will use to clip with
//sh_idx: idx of the shape we will use to clip with
//shape: TODO: fill this at the end of parsing all objects,
//consider how that changes functions & data structures we are
//using, how we iterate through the objects to render more precisely
typedef struct s_clip
{
	t_clip_type	type;
	uint64_t	obj_idx;
	uint64_t	sh_idx;
	t_shape		*shape;
}	t_clip;

struct s_shape
{
	t_shape_type	type;
	t_shape_data	data;
	t_clip			clip[CLIP_MAX];
};

//t_transform	trans; //if we decide to add transformations
// to the individual objects
typedef struct s_object
{
	t_object_type	type;
	t_shape			shape[SHAPES_MAX];
	t_color			color;
}	t_object;

bool			is_clip(t_shape *shape, t_world_coord hitpoint);

#endif