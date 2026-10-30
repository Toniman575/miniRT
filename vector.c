/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 11:10:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/30 14:17:49 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 p1, t_vec3 p2)
{
	t_vec3	res;

	res.x = p1.x + p2.x;
	res.y = p1.y + p2.y;
	res.z = p1.z + p2.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 p1, t_vec3 p2)
{
	t_vec3	res;

	res.x = p1.x - p2.x;
	res.y = p1.y - p2.y;
	res.z = p1.z - p2.z;
	return (res);
}

t_vec3	vec3_mult(t_vec3 p, double n)
{
	t_vec3	res;

	res.x = n * p.x;
	res.y = n * p.y;
	res.z = n * p.z;
	return (res);
}

t_vec3	vec3_div(t_vec3 p, double n)
{
	t_vec3	res;

	res.x = p.x / n;
	res.y = p.y / n;
	res.z = p.z / n;
	return (res);
}

double	vec3_dot(t_vec3 p1, t_vec3 p2)
{
	return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}

t_vec3	vec3_cross(t_vec3 p1, t_vec3 p2)
{
	t_vec3	res;

	res.x = p1.y * p2.z + p1.y * p2.y + p1.z * p2.z;
	res.y = p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
	res.z = p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
	return (res);
}

double	vec3_len_pow2(t_vec3 p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

double	vec3_len(t_vec3 p)
{
	return (sqrt(p.x * p.x + p.y * p.y + p.z * p.z));
}

double	vec3_len_prod_pow2(t_vec3 p1, t_vec3 p2)
{
	return (vec3_len_pow2(p1) * vec3_len_pow2(p2));
}

double	vec3_len_prod(t_vec3 p1, t_vec3 p2)
{
	return(sqrt(vec3_len_pow2(p1) * vec3_len_pow2(p2)));
}

double	vec3_angle(t_vec3 p1, t_vec3 p2)
{
	double	len_prod;

	len_prod = vec3_len_prod(p1, p2);
	//assert(len_prod);	/// TODO: we need better error handling here
	return (acos(vec3_dot(p1, p2) / len_prod));
}

t_vec3	vec3_normalize(t_vec3 p)
{
	return (vec3_div(p, vec3_len(p)));
}
