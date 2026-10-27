/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:09:53 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 14:12:48 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// TODO: Should file be in state?

void	init(t_state *state, char *file) {
	parse(&state, file);
	init_mlx(&state);
}