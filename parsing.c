/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 21:38:43 by sancuta           #+#    #+#             */
/*   Updated: 2026/11/01 23:43:31 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_open(char *path, int oflag)
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
}

void	parse_scene(t_state *state, char *path)
{
	int			fd;
	char		*line;
	size_t		i;
	t_arena		objects;
	uint32_t	offset;
	t_object	obj;
	uint8_t		mask;		// 0b00000 0 0 0
						//         L C A
	fd = ft_open(path, O_RDONLY);
	objects = arena_init(ARENA_SIZE, sizeof(t_object));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		len = strlen(line);
		i = 0;
		while (ft_isspace(line[i]))
			++i;
		if (line[i] == 'A' && ~(mask & 0x1))
		{
			mask | 0x1;
			offset = arena_alloc(objects, sizeof(t_object), _Alignof(t_object));
			obj = (t_object)objects.buffer[offset];
			while (ft_isspace(line[i]))
				++i;
			obj.ambient.brightness = ft_atod(&line[i]);
			while (ft_isspace(line[i]))
				++i;
			obj.color = ft_atoi(&line[i]);
		}
		else if (line[i] == 'C' && ~(mask & 0x2))
		{
			mask | 0x2;
		}
		else if (line [i] == 'L' && ~(mask & 0x4))
		{
			mask | 0x4;
		}
		else if (line [i] == 'L' && ~(mask & 0x4))
	}
}


