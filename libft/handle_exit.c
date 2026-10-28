/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:24:18 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/27 09:06:32 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_status_msg(t_exit_data exit_data)
{
	if (exit_data.status)
	{
		if (exit_data.prefix)
		{
			ft_putstr_fd(exit_data.prefix, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		if (exit_data.name)
		{
			ft_putstr_fd(exit_data.name, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putendl_fd(exit_data.message, STDERR_FILENO);
	}
}
