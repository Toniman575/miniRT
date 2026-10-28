/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:19:28 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/27 08:05:06 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <limits.h>

static bool	is_invalid_val(const char *nptr, long res, size_t i, int sign)
{
	bool	is_invalid;

	is_invalid = (sign == 1 && res > ((LLONG_MAX - nptr[i] + 48) / 10))
		|| (sign == -1 && res < ((LLONG_MIN + nptr[i] - 48) / 10));
	if (is_invalid)
		errno = EINVAL;
	return (is_invalid);
}

/*	pay attention to the wording in strtol(3):
		"The  string  may  begin  with an arbitrary amount of
		white space (as determined by isspace(3)) followed by
		a single optional '+' or '-' sign.
	only **one** sign check is needed!*/

long	ft_atol(const char *nptr)
{
	size_t	i;
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		if (is_invalid_val(nptr, res, i, sign))
			return (0);
		res = res * 10 + sign * (nptr[i] - 48);
		i++;
	}
	return (res);
}
