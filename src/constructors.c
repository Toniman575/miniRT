/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:54:15 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 14:29:12 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"

t_vec3	new_vec3(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_world_coord	new_world_coord(double x, double y, double z)
{
	t_world_coord	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_color	new_color(t_color_component r, t_color_component g, t_color_component b)
{
	t_color	new;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

size_t	alloc_object(t_state *state)
{
	return (arena_alloc(&state->objects, sizeof(t_object), _Alignof(t_object)));
}

t_intersection	new_intersection(t_object *object, t_shape *shape, double t,
		t_world_coord hitpoint)
{
	return ((t_intersection){t, hitpoint, shape, object});
}
