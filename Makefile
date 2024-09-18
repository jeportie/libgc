# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 21:02:39 by jeportie          #+#    #+#              #
#    Updated: 2024/07/11 10:52:53 by jeportie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = 	ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
      	ft_isprint.c ft_memcmp.c ft_strncmp.c ft_tolower.c ft_toupper.c \
      	ft_bzero.c ft_calloc.c ft_memchr.c ft_memcpy.c ft_memmove.c \
      	ft_memset.c ft_strchr.c ft_strdup.c ft_strnstr.c ft_strrchr.c \
      	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_substr.c ft_strjoin.c \
      	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
      	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
      	ft_realloc.c get_next_line.c ft_atol.c \
      	ft_utoa_base.c ft_apply_width.c ft_handle_hash_flag.c \
      	ft_handle_space_flag.c ft_parse_flags.c ft_buffer_add.c \
      	ft_handle_hexadecimal.c ft_handle_string.c ft_parse_format.c \
      	ft_printf_globals.c ft_buffer_flush.c ft_handle_int.c ft_isconvert_spec.c \
      	ft_printf.c ft_check_format.c ft_handle_plus_flag.c ft_isflag.c \
      	ft_ulltoa_base.c ft_handle_char.c ft_handle_pointer.c ft_apply_precision.c \
		ft_nbr_len.c \
		ft_check_fd.c \
		ft_check_malloc.c \
		ft_check_pid.c \
		ft_getenv.c \
		ft_find_cmd_path.c \
		gc_cleanup.c \
		gc_collect.c \
		gc_fd_register.c \
		gc_globals.c \
		gc_malloc.c \
		gc_nest_register.c \
		gc_register.c \
		gc_mark_lock.c 


BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
            ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
            ft_lstmap.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
