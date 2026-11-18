/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:21:45 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 15:27:03 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef uint8_t		t_color_component;
typedef uint32_t	t_xcolor;

typedef struct s_color
{
	t_color_component	r;
	t_color_component	g;
	t_color_component	b;
}	t_color;

t_color		new_color(t_color_component r, t_color_component g,
				t_color_component b);
t_xcolor	x_color_from_color(t_color color);

#endif