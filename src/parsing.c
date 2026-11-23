/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 21:38:43 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/23 12:58:26 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "get_next_line.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef DEBUG
# include <stdio.h>
#endif

int	ft_open(t_state *state, char *path, int oflag)
{
	int		fd;
	while (true)
	{
		errno = 0;
		fd = open(path, oflag);
		if (fd >= 0)
			break;
		else if (errno != EINTR)
			handle_exit(state, (t_exit_data){"minirt", "parse_scene",
				strerror(errno), EXIT_FAILURE});
	}
	return (fd);
}

void	parse_scene(t_state *state, char *path)
{
	int			fd;
	char		*line;
	size_t		i;
	ssize_t		len;
//	size_t		offset;
//	t_object	*obj;
	uint8_t		mask;		// 0b00000 0 0 0
							//         L C A
	fd = ft_open(state, path, O_RDONLY);
	mask = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		i = 0;
		while (ft_isspace(line[i]))
			++i;
		if (line[i] == 'A' && ~(mask & 0x1))
		{
			mask |= 0x1;
			while (ft_isspace(line[i]))
				++i;
			state->ambient.brightness = ft_atod(&line[i]);
			len = ft_indchr(&line[i], ' ');
			if (len == -1)
				/*handle_exit()*/;
			i += len;
			while (ft_isspace(line[i]))
				++i;
			state->ambient.color.r = ft_atoi(&line[i]);
			if (!state->ambient.color.r && errno == EINVAL)
				/*handle_exit()*/;
			len = ft_indchr(&line[i], ',');
			if (len == -1)
				/*handle_exit()*/;
			i += len;
			state->ambient.color.g = ft_atoi(&line[i]);
			if (!state->ambient.color.g && errno == EINVAL)
				/*handle_exit()*/;
			len = ft_indchr(&line[i], ',');
			if (len == -1)
				/*handle_exit()*/;
			i += len;
			state->ambient.color.b = ft_atoi(&line[i]);
			if (!state->ambient.color.g && errno == EINVAL)
				/*handle_exit()*/;
#ifdef DEBUG
			printf("r = %d\n", state->ambient.color.r);
			printf("g = %d\n", state->ambient.color.g);
			printf("b = %d\n", state->ambient.color.b);
#endif
		}
/*
		else if (line[i] == 'C' && ~(mask & 0x2))
		{
			mask |= 0x2;
			while (ft_isspace(line[i]))
				++i;
			state->camera.pos.x = ft_atod(&line[i])
			if (!state->camera.pos.x && errno == EINVAL)
*/				/*handle_exit()*//*;
			i += ft_indchr(&line[i], ',');
		}
		else if (line [i] == 'L' && ~(mask & 0x4))
		{
			mask |= 0x4;
			offset = arena_alloc(objects, sizeof(t_object), _Alignof(t_object));
			obj = (t_object)(objects.buf[offset]);
			obj->type = OBJ_LIGHT;
		}
*/
		free(line);
	}
}


