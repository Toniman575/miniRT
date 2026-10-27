/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:46:09 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 22:47:11 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// TODO: Constructors and setters. Conversions between types.

#ifndef MATH_H
# define MATH_H

# include <stdint.h>
# include "result.h"

typedef uint16_t	t_coord2d;

typedef double		t_coord3d;

typedef struct s_screen_coord
{
	t_coord2d	x;
	t_coord2d	y;
}	t_screen_coord;

typedef struct s_vec3
{
	t_coord3d	x;
	t_coord3d	y;
	t_coord3d	z;
}	t_vec3;

typedef t_vec3	t_world_coord;

typedef struct s_ray
{
	t_world_coord	start;
	t_vec3			direction;
}	t_ray;

t_result	normalize(t_vec3 vec);
t_result	dot_product(t_vec3 vec1, t_vec3 vec2);
t_result	reflect(t_vec3 vec);
t_result	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_result	vec3_mul(t_vec3 vec1, t_vec3 vec2);
t_result	length(t_vec3 vec);
double		world_distance(t_world_coord coord1, t_world_coord coord2);

#endif
