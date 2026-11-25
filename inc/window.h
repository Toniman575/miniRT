/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:25:31 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 17:25:56 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <stdint.h>

typedef uint16_t	t_pixel;
typedef uint16_t	t_coord2d;

typedef struct s_dim2d
{
	t_pixel	width;
	t_pixel	height;
}	t_dim2d;

typedef struct s_win_data
{
	t_dim2d	dim;
	void	*ptr;
}	t_win_data;

typedef struct s_img_data
{
	t_dim2d	dim;
	void	*ptr;
	char	*buf;
	int		pixels_per_line;
	int		byte_order;
}	t_img_data;

typedef struct s_screen_coord
{
	t_coord2d	x;
	t_coord2d	y;
}	t_screen_coord;

/// view port coords can be negative
typedef struct s_view_port_coord
{
	int16_t	x;
	int16_t	y;
}	t_view_port_coord;

#endif