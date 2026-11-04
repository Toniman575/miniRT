/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:40:25 by asadik            #+#    #+#             */
/*   Updated: 2026/11/04 20:30:39 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// TODO: Should filename be in the state struct?
/// TODO: Viewport field in camera struct.

#include "utils.h"

void	validate_scene_path(int argc, char *path)
{
	size_t	len;

	if (argc != 2)
	{
		handle_exit(NULL, (t_exit_data){"minirt",
			"wrong amount of parameters.\nUsage",
			"./minirt /path/to/scene.rt", EXIT_FAILURE});
	}
	len = ft_strlen(path);
	if (ft_strncmp(path + len - 3, ".rt", 4))
		handle_exit(NULL, (t_exit_data){"minirt", "parse_scene",
			"not a .rt file", EXIT_FAILURE});
}

int	main(int argc, char **argv)
{
	t_state	state;

	validate_scene_path(argc, argv[1]);
	init(&state, argv[1]);
	main_loop(&state);
	mlx_loop(state.mlx_ptr);
	handle_exit(&state, (t_exit_data){NULL, NULL, NULL, EXIT_SUCCESS});
}
