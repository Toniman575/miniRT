/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 11:07:54 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/30 14:41:10 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// Squared distance to avoid sqrt. We only need the distance for comparison, so this works out.
double	world_distance_squared(t_world_coord start, t_world_coord end)
{
	t_world_coord	distance;

	distance.x =start.x - end.x;
	distance.y =start.y - end.y;
	distance.z =start.z - end.z;
	return (start.x * end.x + start.y * end.y + start.z * end.z);
}
