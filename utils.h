/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:42:25 by asadik            #+#    #+#             */
/*   Updated: 2026/10/30 14:41:44 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft/libft.h"
# include "vector.h"

# define MSB_FIRST 1
# define LSB_FIRST 0

# define E_MLX_INIT	"Failed to establish a connection to the X Server."
# define E_MLX_WIN	"Failed to create a window."
# define E_MLX_IMG	"Failed to create an image."

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define IMG_WIDTH	1920
# define IMG_HEIGHT	1080

typedef uint8_t		t_color_component;
typedef uint32_t	t_xcolor;
typedef uint8_t		fov;

typedef struct s_quaternion
{
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quaternion;

typedef struct	s_color
{
	t_color_component	a;
	t_color_component	r;
	t_color_component	g;
	t_color_component	b;
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

typedef uint16_t	t_coord2d;

typedef t_vec3	t_world_coord;

typedef struct s_camera
{
	t_world_coord	pos;
	t_quaternion	rotation;
	double			pan_speed;
	double			rot_speed;
	fov				fov;
}	t_camera;

typedef struct s_object t_object;

typedef struct s_state
{
	t_win_data	win;
	t_img_data	img;
	void		*mlx_ptr;
	t_object	*objects;
	uint16_t	objects_n;
	t_camera	camera;
}	t_state;

typedef struct s_screen_coord
{
	t_coord2d	x;
	t_coord2d	y;
}	t_screen_coord;

typedef struct s_view_port_coord
{
	int16_t	x;
	int16_t	y;
}	t_view_port_coord;

typedef struct s_ray
{
	t_world_coord	origin;
	t_vec3			dir;
}	t_ray;

typedef struct s_light
{
	t_world_coord		pos;
}	t_light;

typedef struct s_sphere
{
	t_world_coord		center;
	double				diameter;
}	t_sphere;

typedef struct s_plane
{
	t_world_coord		pos;
	t_vec3				rot;
}	t_plane;

typedef struct s_cylinder
{
	t_world_coord		center;
	t_vec3				rot;
	double				diameter;
	double				height;
}	t_cylinder;

typedef union u_object_data
{
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_data;

typedef enum e_object_type
{
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_object_data	data;
	t_xcolor		color;
}	t_object;

typedef struct s_intersection
{
	t_world_coord	pos;
	t_object		*object;
}	t_intersection;

typedef enum e_rtype
{
	RT_ERROR,
	RT_INT,
}	t_rtype;

typedef union u_rvalue
{
	char	*error;
	int		n;
}	t_rvalue;

typedef struct s_result
{
	t_rtype		type;
	t_rvalue	value;
}	t_result;

typedef enum e_otype
{
	OT_NONE,
	OT_INTERSECTION,
}	t_otype;

typedef union u_ovalue
{
	t_intersection	intersection;
}	t_ovalue;

typedef struct s_option
{
	t_otype		type;
	t_ovalue	value;
}	t_option;

t_option	xchecker(t_object *object, t_ray *ray);
t_result	reflect(t_vec3 vec);
double		world_distance_squared(t_world_coord start, t_world_coord end);
void		init(t_state *state, char *file);
int			handle_key_press(int keycode, void *data);
int			handle_key_release(int keycode, void *data);
int			main_loop(void *data);
int			call_exit(void *data);
void		render(t_state *state);
void		handle_exit(t_state *state, t_exit_data data);

#endif
