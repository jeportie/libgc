/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:59:02 by jeportie          #+#    #+#             */
/*   Updated: 2025/02/10 15:36:24 by jeportie         ###   ########.fr       */
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
	size_t				size;
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

extern t_gc	g_gcl;

/* GARBAGE_COLLECTOR */
void			gc_init(void);

void			gc_cleanup(void);
void			gc_collect(void);

void			*gc_malloc(size_t size);
void			*gc_realloc(void *ptr, size_t size);
void			gc_register(void *ptr);
void			gc_nest_register(void *ptr);
void			gc_fd_register(int fd);
void			gc_temp_file_register(const char *filename);
void			gc_free(void *ptr);
void			gc_lock(void *ptr);
void			gc_nest_lock(void *ptr);
void			gc_unlock(void *ptr);
void			gc_mark(void *ptr);

void			*gc_memcpy(void *dest, const void *src, size_t n);
char			*gc_strjoin(char *s1, char *s2);
int				gc_strlen(const char *str);
char			*gc_strdup(const char *s);

#endif /*LIBGC_H*/
