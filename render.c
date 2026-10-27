/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:11:27 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 23:07:52 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	render(void *data)
{
	t_state	*state;

	state = (t_state *)data;
	/*
	update_timestamp(state);
	handle_camera(state);
	handle_objects(state);
	if (state.timestamp > state.framerate)
	{
		draw(state);
	}
	*/
	draw(state);
	return (1);
}
