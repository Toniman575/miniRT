/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:40:25 by asadik            #+#    #+#             */
/*   Updated: 2026/10/28 15:11:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// TODO: Should filename be in the state struct? Viewport field in camera struct.

#include "utils.h"
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	t_state state;

	if (argc != 2)
	{
		handle_exit(&((t_state){0}), (t_exit_data){"minirt", 
			"wrong amount of parameters.\nUsage", "./minirt /path/to/scene.rt",
			EXIT_FAILURE});
		return (1);
	};
	init(&state, argv[1]);
	main_loop(&state);
	mlx_loop(state.mlx_ptr);
	handle_exit(&state, (t_exit_data){NULL, NULL, NULL, EXIT_SUCCESS});
}
