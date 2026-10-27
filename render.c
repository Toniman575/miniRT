/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:11:27 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 17:00:45 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	render(t_state *state)
{
	update_timestamp(state);
	handle_camera(state);
	handle_objects(state);
	if (state.timestamp > state.framerate)
	{
		draw(state);
	}
}