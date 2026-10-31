/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 12:14:41 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/31 17:06:05 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef double	t_coord3d;
typedef struct s_vec3
{
	t_coord3d	x;
	t_coord3d	y;
	t_coord3d	z;
}	t_vec3;

t_vec3	new_vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 p1, t_vec3 p2);
t_vec3	vec3_sub(t_vec3 p1, t_vec3 p2);
t_vec3	vec3_mult(t_vec3 p, double n);
t_vec3	vec3_div(t_vec3 p, double n);
double	vec3_dot(t_vec3 p1, t_vec3 p2);
t_vec3	vec3_cross(t_vec3 p1, t_vec3 p2);
double	vec3_len_pow2(t_vec3 p);
double	vec3_len(t_vec3 p);
double	vec3_len_prod_pow2(t_vec3 p1, t_vec3 p2);
double	vec3_len_prod(t_vec3 p1, t_vec3 p2);
double	vec3_angle(t_vec3 p1, t_vec3 p2);
t_vec3	vec3_normalize(t_vec3 p);

#endif
