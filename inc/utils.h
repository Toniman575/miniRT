/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:42:25 by asadik            #+#    #+#             */
/*   Updated: 2026/11/17 04:40:12 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"
# include "get_next_line.h"
# include "arena.h"
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

# define AMBIENT	0x1
# define CAMERA		0x2
# define LIGHT		0x4

# ifndef ARENA_SIZE
#  define ARENA_SIZE 64
# endif

# define EPSILON	1e-9

# define CAM_IN		-1
# define CAM_OUT	1

# define IN		true
# define OUT	false

# define CLIP_MAX 3
# define SHAPES_MAX 3
# define ROOTS_MAX 2

typedef uint8_t		t_color_component;
typedef uint32_t	t_xcolor;
typedef uint8_t		t_fov;

typedef struct s_color
{
	t_color_component	r;
	t_color_component	g;
	t_color_component	b;
}	t_color;

typedef uint16_t	t_pixel;

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

typedef t_vec3		t_world_coord;

typedef struct s_ambient
{
	double	brightness;
}	t_ambient;

typedef struct s_camera
{
	t_world_coord	pos;
	t_quaternion	rotation;
	double			pan_speed;
	double			rot_speed;
	t_fov			fov;
}	t_camera;

typedef struct s_light
{
	t_world_coord	pos;
	double			brightness;
}	t_light;

typedef struct s_state
{
	t_win_data	win;
	t_img_data	img;
	void		*mlx_ptr;
	t_arena		objects;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
}	t_state;

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

typedef struct s_ray
{
	t_world_coord	origin;
	t_vec3			dir;
}	t_ray;

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
	OT_LIN_ROOT,
	OT_QUAD_ROOT,
	OT_COUNT,
}	t_otype;

/*
typedef struct s_disc
{
	t_world_coord	center;
	t_vec3			dir;
	double			radius;
}	t_disc;
*/

typedef struct s_plane
{
	t_world_coord		pos;
	t_vec3				dir;
}	t_plane;

typedef struct s_sphere
{
	t_world_coord	center;
	double			radius;
}	t_sphere;

typedef struct s_tube
{
	t_world_coord	center;
	t_vec3			dir;
	double			radius;
	//height will contribute to the clipping plane's pos = center + dir * ±height/2
}	t_tube;

typedef union u_shape_data
{
	t_plane		plane;
	t_sphere	sphere;
	t_tube		tube;
}	t_shape_data;

typedef enum e_shape_type
{
	SHAPE_NONE,
	SHAPE_CIRCLE,
	SHAPE_PLANE,
	SHAPE_SPHERE,
	SHAPE_TUBE,
	SHAPE_COUNT
}	t_shape_type;

typedef enum e_object_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_COUNT
}	t_object_type;

typedef enum e_clip_type
{
	CT_NONE,
	CT_POS, 		// draw the side the normal points towards
	CT_NEG, 		// draw the side the normal doesnt point towards
	CT_COUNT
}	t_clip_type;

typedef struct s_shape	t_shape;
typedef struct s_clip
{
	t_clip_type	type;		//if non zero used to control how the shape is used as a clip
	uint64_t	obj_idx;	//idx of the object we will use to clip with
	uint64_t	sh_idx;		//idx of the shape we will use to clip with
	t_shape		*shape;		//TODO: fill this at the end of parsing all objects, consider how that changes functions & data structures we are using, how we iterate through the objects to render more precisely.
}	t_clip;

struct s_shape
{
	t_shape_type	type;
	t_shape_data	data;
	t_clip			clip[CLIP_MAX];
};

typedef struct s_object
{
	t_object_type	type;
	t_shape			shape[SHAPES_MAX];
	t_color			color;
	//t_transform	trans; //if we decide to add transformations to the individual objects
}	t_object;

/// t is the length of the ray from its origin to hitpoint where
/// the intersection happens.
typedef struct s_intersection
{
	double			t;
	t_world_coord	hitpoint;
	t_shape			*shape;
	t_object		*object;
}	t_intersection;

typedef union u_ovalue
{
	t_intersection	intersection;
	double			t;
	double			ts[2];
}	t_ovalue;

typedef struct s_option
{
	t_otype		type;
	t_ovalue	value;
}	t_option;

typedef struct s_lin_eq
{
	double	a;
	double	b;
}	t_lin_eq;

typedef struct s_quad_eq
{
	double	a;
	double	b_half;
	double	c;
}	t_quad_eq;

t_world_coord	new_world_coord(double x, double y, double z);
t_option		intersect_object(t_object *object, t_ray *ray);
t_result		reflect(t_vec3 vec);
void			init(t_state *state, char *file);
int				handle_key_press(int keycode, void *data);
int				handle_key_release(int keycode, void *data);
int				main_loop(void *data);
int				call_exit(void *data);
void			render(t_state *state);
void			handle_exit(t_state *state, t_exit_data data);
t_color			new_color(t_color_component r, t_color_component g,
					t_color_component b);
t_option		cast_ray(t_state *state, t_ray ray);
t_xcolor		get_color_from_ray(t_state *state, t_option x, t_ray ray);
t_xcolor		x_color_from_color(t_color color);
t_vec3			get_normal(t_intersection x);
t_vec3			get_normal_facing_ray(t_intersection x, t_ray ray);
void			cleanup(t_state *state);
void			parse_scene(t_state *state, char *path);
bool			is_clip(t_shape *shape, t_world_coord hitpoint);

#endif
