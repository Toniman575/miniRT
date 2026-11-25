/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 21:12:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/25 18:08:46 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/keysym.h>

#include "utils.h"

int	handle_key_press(int keycode, void *data)
{
	if (keycode == XK_Escape)
		call_exit(data);
	return (1);
}

int	main_loop(void *data)
{
	t_state	*state;

	state = (t_state *)data;
	if (!state->redraw)
		return (1);
	/*
	update_timestamp(state);
	handle_camera(state);
	handle_objects(state);
	if (state.timestamp > state.framerate)
	{
		draw(state);
	}
	*/
	render(state);
	state->redraw = false;
	return (1);
}

// int	handle_key_release(int keycode, void *data)
// {
// 	(void)keycode;
// 	(void)data;
// 	/*
// 	t_state	*state;

// 	state = (t_state *)data;
// 	*/
// 	return (1);
// }

int	call_exit(void *data)
{
	t_state	*state;

	state = (t_state *)data;
	handle_exit(state, (t_exit_data){NULL, NULL, NULL, EXIT_SUCCESS});
	return (1);
}
