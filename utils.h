/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:42:25 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 23:40:09 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "shapes.h"

# define MSB_FIRST 1
# define LSB_FIRST 0

# define E_MLX_INIT	"Failed to establish a connection to the X Server."
# define E_MLX_WIN	"Failed to create a window."
# define E_MLX_IMG	"Failed to create an image."

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define IMG_WIDTH	1920
# define IMG_HEIGHT	1080

typedef uint8_t	t_color_component;

typedef struct	s_color
{
	t_color_component	alpha;
	t_color_component	red;
	t_color_component	green;
	t_color_component	blue;
}	t_color;

typedef uint16_t t_pixel;

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
	int		bits_per_pixel;
	int		bytes_per_line;
	int		byte_order;
}	t_img_data;

typedef struct s_state
{
	t_win_data	win;
	t_img_data	img;
	void		*mlx_ptr;
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

void	init(t_state *state, char *file);

int		handle_key_press(int keycode, void *data);
int		handle_key_release(int keycode, void *data);
int		render(void *data);
int		call_exit(void *data);

void	draw(t_state *state);

void	handle_exit(t_state *state, t_exit_data data);
#endif
