/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:01:37 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 14:21:54 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdint.h>

# include "color.h"
# include "vector.h"

typedef uint8_t	t_fov;

typedef struct s_ambient
{
	double		brightness;
	t_color		color;
}	t_ambient;

// center of the top left pixel
// direction change per pixel to the right
// direction change per pixel down
typedef struct s_viewport
{
	t_vec3	top_left;
	t_vec3	sx;
	t_vec3	sy;
}	t_viewport;

typedef struct s_camera
{
	t_world_coord	pos;
	t_quaternion	rotation;
	double			pan_speed;
	double			rot_speed;
	t_fov			fov;
	t_viewport		viewport;
}	t_camera;

typedef struct s_light
{
	t_world_coord	pos;
	double			brightness;
	t_color			color;
}	t_light;

#endif
