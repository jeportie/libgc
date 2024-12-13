# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 21:02:39 by jeportie          #+#    #+#              #
#    Updated: 2024/12/13 17:14:29 by jeportie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgc.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

### BEGIN AUTO GENERATED FILES ###
# List of source files:
SRC = \
  src/gc_fd_register.c \
  src/gc_malloc.c \
  src/gc_mark_lock.c \
  src/gc_nest_register.c \
  src/gc_realloc.c \
  src/gc_register.c \
  src/gc_collect.c \
  src/gc_init.c \
  src/gc_free.c \
  src/gc_cleanup.c \
  src/gc_arena_alloc.c 
### END AUTO GENERATED FILES ###

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
