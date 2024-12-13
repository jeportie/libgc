/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:59:04 by jeportie          #+#    #+#             */
/*   Updated: 2024/12/13 16:01:39 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	gc_free(void *ptr, t_gc *gcl)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	current = gcl->head;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				gcl->head = current->next;
			free(current->ptr);
			current->ptr = NULL;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	exit(EXIT_FAILURE);
}

int	gc_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*gc_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*mem_dest;
	unsigned char	*mem_src;

	if (!dest && !src)
		return (NULL);
	mem_dest = (unsigned char *)dest;
	mem_src = (unsigned char *)src;
	while (n-- && mem_dest && mem_src)
		*mem_dest++ = *mem_src++;
	return (dest);
}

char	*gc_strdup(const char *s, t_gc *gcl)
{
	char	*new_str;
	size_t	s_len;

	s_len = gc_strlen(s);
	new_str = (char *)gc_malloc(sizeof(char) * (s_len + 1), gcl);
	if (!new_str)
		return (NULL);
	new_str = gc_memcpy(new_str, s, s_len + 1);
	return (new_str);
}
