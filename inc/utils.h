/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:42:25 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 16:27:59 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "ray.h"
# include "state.h"

void			init(t_state *state, char *file);
void			parse_scene(t_state *state, char *path);
void			render(t_state *state);
int				main_loop(void *data);
t_option		cast_ray(t_state *state, t_ray ray);
t_xcolor		get_color_from_ray(t_state *state, t_option x, t_ray ray);
int				handle_key_press(int keycode, void *data);
int				handle_key_release(int keycode, void *data);
int				call_exit(void *data);
void			handle_exit(t_state *state, t_exit_data data);
void			cleanup(t_state *state);

#endif
