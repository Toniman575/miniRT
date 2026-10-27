/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:42:25 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 17:15:19 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "shapes.h"

typedef struct s_state
{
	
}	t_state;

typedef enum e_otype
{
	NONE,
	INTERSECTION,
}	t_otype;

typedef union u_ovalue
{
	char			*error;
	t_intersection	intersection;
}	t_ovalue;

typedef struct s_option
{
	t_otype		type;
	t_ovalue	value;
}	t_option;

#endif