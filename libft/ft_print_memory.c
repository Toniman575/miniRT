/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:21:53 by sancuta           #+#    #+#             */
/*   Updated: 2026/08/09 13:22:15 by sancuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	dec_to_hex_n(char *hex, unsigned long dec, int length)
{
	char	*hex_table;

	hex_table = "0123456789abcdef";
	while (length > 0)
	{
		hex[length - 1] = hex_table[dec % 16];
		dec = dec / 16;
		length--;
	}
}

static void	print_hex_addr(int fd, void *addr)
{
	char	buffer[16];
	int		counter;

	counter = 0;
	while (counter < 16)
	{
		buffer[counter] = '0';
		counter++;
	}
	dec_to_hex_n(buffer, (unsigned long) addr, 16);
	write(fd, buffer, 16);
	write(fd, ": ", 2);
}

static void	print_hex_string(int fd, void *addr, unsigned int size)
{
	int		counter;
	int		index;
	char	buffer[40];
	char	*value;

	value = (char *)addr;
	counter = 0;
	index = 0;
	while (index < 16)
	{
		if (index < (int)size)
			dec_to_hex_n(&buffer[counter], (unsigned char)value[index], 2);
		else
		{
			buffer[counter] = ' ';
			buffer[counter + 1] = ' ';
		}
		index++;
		counter += 2;
		if (index % 2 == 0)
			buffer[counter++] = ' ';
	}
	write(fd, buffer, 40);
}

static void	print_char_dot(int fd, void *addr, unsigned int size)
{
	int		counter;
	char	*value;

	value = (char *)addr;
	counter = 0;
	while (counter < 16)
	{
		if (counter < (int)size)
		{
			if (value[counter] < 32 || value[counter] > 126)
				write(fd, ".", 1);
			else
				write(fd, value + counter, 1);
		}
		counter++;
	}
}

void	*ft_print_memory(int fd, void *addr, size_t size)
{
	int	lines;
	int	counter;

	lines = (size + 15) / 16;
	if (!size)
		return (NULL);
	counter = 0;
	while (counter < lines - 1)
	{
		print_hex_addr(fd, addr + counter * 16);
		print_hex_string(fd, addr + counter * 16, size - counter * 16);
		print_char_dot(fd, addr + counter * 16, size - counter * 16);
		write(fd, "\n", 1);
		counter++;
	}
	print_hex_addr(fd, addr + counter * 16);
	print_hex_string(fd, addr + counter * 16, size - counter * 16);
	print_char_dot(fd, addr + counter * 16, size - counter * 16);
	write(2, "\n", 1);
	return (addr);
}

/*
int main(void)
{
	ft_print_memory("Bonjour les aminpeut faire avec", 40);
	return (0);
}
*/
