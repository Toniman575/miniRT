/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 17:14:26 by asadik            #+#    #+#             */
/*   Updated: 2026/10/27 21:51:22 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESULT_H
# define RESULT_H

typedef enum e_rtype
{
	ERROR,
	INT,
}	t_rtype;

typedef union u_rvalue
{
	char	*error;
	int		n;
}	t_rvalue;

typedef struct s_result
{
	t_rtype		type;
	t_rvalue	value;
}	t_result;

#endif
