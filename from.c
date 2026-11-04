/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:54:45 by asadik            #+#    #+#             */
/*   Updated: 2026/11/04 13:52:37 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_xcolor	x_color_from_color(t_color color)
{
	return (((t_xcolor)color.r << 16)
		| ((t_xcolor)color.g << 8)
		| (t_xcolor)color.b);
}
