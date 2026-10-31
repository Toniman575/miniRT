/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:54:15 by asadik            #+#    #+#             */
/*   Updated: 2026/10/31 17:07:17 by asadik           ###   ########.fr       */
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
