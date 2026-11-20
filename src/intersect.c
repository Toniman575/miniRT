/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 10:42:59 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/20 15:09:51 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_option	intersect_object(t_object *object, t_ray *ray)
{
	t_option	option;

	option.type = OT_NONE;
	if (object->type == OBJ_PLANE)
		option = intersect_plane(object, object->shape, ray);
	else if (object->type == OBJ_SPHERE)
		option = intersect_sphere(object, object->shape, ray);
	else if (object->type == OBJ_CYLINDER)
		option = intersect_cylinder(object, object->shape, ray);
	return (option);
}
