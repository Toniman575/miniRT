/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:46:11 by asadik            #+#    #+#             */
/*   Updated: 2026/10/31 16:46:30 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
