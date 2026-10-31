/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 11:10:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/31 16:55:28 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

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
	return (sqrt(vec3_len_pow2(p1) * vec3_len_pow2(p2)));
}

t_vec3	vec3_normalize(t_vec3 p)
{
	return (vec3_div(p, vec3_len(p)));
}
