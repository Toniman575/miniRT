/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:39:42 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/17 02:39:14 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_point_plane(t_plane plane, t_world_coord p, t_clip_type type)
{
	t_vec3	pp;

	pp = vec3_sub(p, plane.pos);
	if (type == CT_POS
		&& vec3_dot(pp, plane.dir) < -EPSILON)
		return (false);
	if (type == CT_NEG
		&& vec3_dot(pp, plane.dir) > EPSILON)
		return (false);
	return (true);
}

bool	is_point_sphere(t_sphere sphere, t_world_coord p, t_clip_type type)
{
	t_vec3	pc;

	pc = vec3_sub(sphere.center, p);
	if (type == CT_POS
		&& vec3_len_pow2(pc) - pow(sphere.radius, 2) < -EPSILON)
		return (false);
	if (type == CT_NEG
		&& vec3_len_pow2(pc) - pow(sphere.radius, 2) > EPSILON)
		return (false);
	return (true);
}

bool	is_point_tube(t_tube tube, t_world_coord p, t_clip_type type)
{
	t_vec3	radial;

	radial = vec3_cross(vec3_sub(p, tube.center), tube.dir);
	if (type == CT_POS
		&& vec3_len_pow2(radial) - pow(tube.radius, 2) < -EPSILON)
		return (false);
	if (type == CT_NEG
		&& vec3_len_pow2(radial) - pow(tube.radius, 2) > EPSILON)
		return (false);
	return (true);
}

bool	is_clip(t_shape *shape, t_world_coord hitpoint)
{
	t_shape	cs;
	size_t	i;

	i = -1;
	while (shape->clip[++i].type)
	{
		cs = *shape->clip[i].shape;
		if (cs.type == SHAPE_PLANE
			&& !is_point_plane(cs.data.plane, hitpoint, shape->clip[i].type))
			return (false);
		else if (cs.type == SHAPE_SPHERE
			&& !is_point_sphere(cs.data.sphere, hitpoint, shape->clip[i].type))
			return (false);
		else if (cs.type == SHAPE_TUBE
			&& !is_point_tube(cs.data.tube, hitpoint, shape->clip[i].type))
			return (false);
	}
	return (true);
}
