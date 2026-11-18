/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:19:00 by asadik            #+#    #+#             */
/*   Updated: 2026/11/18 15:20:42 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define MSB_FIRST 1
# define LSB_FIRST 0

# define E_MLX_INIT	"Failed to establish a connection to the X Server."
# define E_MLX_WIN	"Failed to create a window."
# define E_MLX_IMG	"Failed to create an image."

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define IMG_WIDTH	1920
# define IMG_HEIGHT	1080

# ifndef ARENA_SIZE
#  define ARENA_SIZE 64
# endif

# define EPSILON	1e-9

# define AMBIENT	0x1
# define CAMERA		0x2
# define LIGHT		0x4

#endif