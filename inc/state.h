/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:11:08 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 15:20:14 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "arena.h"
# include "window.h"
# include "scene.h"

typedef struct s_state
{
	t_win_data	win;
	t_img_data	img;
	void		*mlx_ptr;
	t_arena		objects;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
	bool		redraw;
}	t_state;

#endif