/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:01:37 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:28:09 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdint.h>

# include "vector.h"

typedef uint8_t		t_fov;

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

#endif