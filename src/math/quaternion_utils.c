/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 17:54:11 by asadik            #+#    #+#             */
/*   Updated: 2026/11/20 15:11:33 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"

t_quaternion	quat_from_aa(double rad, t_vec3 axis)
{
	t_quaternion	res;
	double			sin_rad_half;

	axis = vec3_normalize(axis);
	sin_rad_half = sin(rad / 2.0);
	res.w = cos(rad / 2.0);
	res.x = axis.x * sin_rad_half;
	res.y = axis.y * sin_rad_half;
	res.z = axis.z * sin_rad_half;
	return (res);
}
