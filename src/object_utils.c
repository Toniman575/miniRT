/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 17:54:43 by asadik            #+#    #+#             */
/*   Updated: 2026/11/09 18:12:10 by asadik           ###   ########.fr       */
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
