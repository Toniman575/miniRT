/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 21:12:50 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/27 22:56:48 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	handle_key_press(int keycode, void *data)
{
	(void)keycode;
	(void)data;
	/*
	t_state	*state;

	state = (t_state *)data;
	*/
	return (1);
}

int	handle_key_release(int keycode, void *data)
{
	(void)keycode;
	(void)data;
	/*
	t_state	*state;

	state = (t_state *)data;
	*/
	return (1);
}

int	call_exit(void *data)
{
	t_state	*state;

	state = (t_state *)data;
	handle_exit(state, (t_exit_data){NULL, NULL, NULL, EXIT_SUCCESS});
	return (1);
}
