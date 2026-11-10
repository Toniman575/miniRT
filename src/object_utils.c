/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:54:43 by asadik            #+#    #+#             */
/*   Updated: 2026/11/10 13:46:49 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_vec3	get_normal(t_intersection intersection)
{
	if (intersection.object->type == OBJ_SPHERE)
		return (vec3_normalize(
				vec3_sub(intersection.hitpoint,
					intersection.object->data.sphere.center)));
	else if (intersection.object->type == OBJ_PLANE)
		return (intersection.object->data.plane.dir);
	else
		return (new_vec3(0., 0., 0.));
}

t_vec3	get_facing_normal(t_state *state, t_intersection x)
{
	t_vec3	normal;
	t_vec3	facing;

	normal = get_normal(x);
	facing = vec3_normalize(vec3_sub(state->camera.pos, x.hitpoint));
	if (vec3_dot(normal, facing) < -EPSILON)
		normal = vec3_mult(normal, -1.);
	return (normal);
}
