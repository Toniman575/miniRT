/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:40:25 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 17:15:56 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	main(int argc, char **argv)
{
	t_state state;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments.");
		return (1);
	};
	init(&state);
	render(&state);
	cleanup(&state);
}