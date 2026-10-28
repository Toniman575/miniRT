# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancuta <sancuta@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 23:38:42 by sancuta           #+#    #+#              #
#    Updated: 2026/10/27 19:04:54 by sancuta          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC ?= cc
CFLAGS ?= -MMD -MP -Wall -Wextra -Werror
ARFLAGS = -rcs
PRINTF_DIR = printf
GNL_DIR    = gnl
ARENA_DIR  = arena

SRCS = \
		ft_isalpha.c \
		ft_issign.c \
		ft_isspace.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_indchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_atol.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_print_memory.c \
		ft_write.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		handle_exit.c \
		sig_digits_strlen.c \
		$(PRINTF_DIR)/ft_get_form_spec.c \
		$(PRINTF_DIR)/ft_printf.c \
		$(PRINTF_DIR)/ft_printf_padding.c \
		$(PRINTF_DIR)/ft_printf_utils.c \
		$(PRINTF_DIR)/ft_print_handler.c \
		$(PRINTF_DIR)/ft_prt_hex.c \
		$(PRINTF_DIR)/ft_prt_int.c \
		$(PRINTF_DIR)/ft_prt_uint.c \
		$(PRINTF_DIR)/ft_put_nbr_base.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c \
		$(ARENA_DIR)/arena_alloc_reset.c \
		$(ARENA_DIR)/arena_init_free.c \
		$(ARENA_DIR)/arena_save_restore.c \
		$(ARENA_DIR)/arena_strings.c \
		$(ARENA_DIR)/arena_itoa.c \
		$(ARENA_DIR)/arena_split.c \
		$(ARENA_DIR)/arena_pointer.c \
		$(ARENA_DIR)/arena_cleanup.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: .release $(NAME)

.release:
	if [ -f .debug ]; then $(MAKE) fclean; fi
	touch .release

$(NAME): $(OBJS)
	ar $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME) .debug .release

re: fclean all

debug: CFLAGS += -g
debug: .debug $(NAME)

.debug:
	if [ -f .release ]; then $(MAKE) fclean; fi
	touch .debug

.PHONY: all clean fclean re debug

-include $(DEPS)
