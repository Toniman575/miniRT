/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:55:53 by sancuta           #+#    #+#             */
/*   Updated: 2026/08/10 18:34:45 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static size_t	count_symbols(int64_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

size_t	arena_itoa(t_arena *dest, const int nbr)
{
	size_t	offset;
	int64_t	n;
	size_t	len;

	n = (int64_t)nbr;
	len = count_symbols(n);
	offset = arena_alloc(dest, len + 1, 1);
	if (n < 0)
	{
		dest->buf[offset] = '-';
		n = -n;
	}
	dest->buf[offset + len] = '\0';
	if (!n)
		dest->buf[offset] = '0';
	while (n)
	{
		len--;
		dest->buf[offset + len] = (char)((n % 10) + 48);
		n /= 10;
	}
	return (offset);
}
