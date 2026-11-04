/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:46:14 by asadik            #+#    #+#             */
/*   Updated: 2026/10/31 17:08:55 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "vector.h"
#include <math.h>

double	vec3_dot(t_vec3 p1, t_vec3 p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

t_vec3	vec3_cross(t_vec3 p1, t_vec3 p2)
{
	t_vec3	res;

	res.x = p1.y * p2.z - p1.z * p2.y;
	res.y = p1.z * p2.x - p1.x * p2.z;
	res.z = p1.x * p2.y - p1.y * p2.x;
	return (res);
}

double	vec3_angle(t_vec3 p1, t_vec3 p2)
{
	double	len_prod;

	len_prod = vec3_len_prod(p1, p2);
	//assert(len_prod);	/// TODO: we need better error handling here
	return (acos(vec3_dot(p1, p2) / len_prod));
}

t_vec3	rotate_vec3(t_quaternion quat, t_vec3 vec)
{
	t_vec3	qv;
	t_vec3	t;

	qv = new_vec3(quat.x, quat.y, quat.z);
	t = vec3_mult(vec3_cross(qv, vec), 2.);
	return (vec3_add(vec3_add(vec, vec3_mult(t, quat.w)), vec3_cross(qv, t)));
}
