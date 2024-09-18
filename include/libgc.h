/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:59:02 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/18 14:28:52 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGC_H
# define LIBGC_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_gc_node
{
	void				*ptr;
	bool				is_marked;
	bool				is_locked;
	bool				is_array;
	int					fd;
	char				*temp_file;
	struct s_gc_node	*next;
}				t_gc_node;

typedef struct s_garbage_collector
{
	t_gc_node	*head;
}				t_gc;

extern t_gc			g_garbage_collector;

/* GARBAGE_COLLECTOR */
void			*gc_malloc(size_t size);
void			gc_register(void *ptr);
void			gc_nest_register(void *ptr);
void			gc_fd_register(int fd);
void			gc_temp_file_register(const char *filename);
void			gc_cleanup(void);
void			gc_collect(void);
void			gc_lock(void *ptr);
void			gc_nest_lock(void *ptr);
void			gc_unlock(void *ptr);
void			gc_mark(void *ptr);

char			*gc_strjoin(char const *s1, char const *s2);

#endif /*LIBGC_H*/
