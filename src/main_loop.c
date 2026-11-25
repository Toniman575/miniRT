/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:11:27 by asadik            #+#    #+#             */
/*   Updated: 2026/11/25 15:22:16 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
