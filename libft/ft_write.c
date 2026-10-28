/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:33:17 by sancuta           #+#    #+#             */
/*   Updated: 2026/10/27 19:05:47 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_write(int fd, const char* s, t_write_type wt)
{
	ssize_t	ret;
	ssize_t	i;
	size_t	len;

	if (!s)
	{
		errno = EFAULT;
		return (-1);
	}
	if (wt == WT_CHAR)
		len = 1;
	else
		len = ft_strlen(s);
	ret = 0;
	while ((size_t)ret < len)
	{
		errno = 0;
		i = write(fd, s + ret, len - ret);
		if (i < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		ret += i;
	}
	return (ret);
}
