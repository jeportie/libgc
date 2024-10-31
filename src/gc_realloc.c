/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:55:40 by jeportie          #+#    #+#             */
/*   Updated: 2024/10/31 08:23:36 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

static void	*helper(t_gc_node *current, void *ptr, size_t size, t_gc *gcl)
{
	size_t		old_size;
	size_t		copy_size;
	void		*new_ptr;

	if (current->ptr == ptr)
	{
		old_size = current->size;
		new_ptr = malloc(size);
		if (!new_ptr)
		{
			write(2, "Error: gc_realloc malloc failed.\n", 33);
			gc_cleanup(gcl);
			exit(EXIT_FAILURE);
		}
		if (old_size < size)
			copy_size = old_size;
		else
			copy_size = size;
		gc_memcpy(new_ptr, ptr, copy_size);
		free(current->ptr);
		current->ptr = new_ptr;
		current->size = size;
		return (new_ptr);
	}
	return (NULL);
}

void	*gc_realloc(void *ptr, size_t size, t_gc *gcl)
{
	t_gc_node	*current;
	void		*new_ptr;

	if (!ptr)
		return (gc_malloc(size, gcl));
	if (size == 0)
	{
		gc_free(ptr, gcl);
		return (NULL);
	}
	current = gcl->head;
	while (current)
	{
		new_ptr = helper(current, ptr, size, gcl);
		if (!new_ptr)
			current = current->next;
		else
			return (new_ptr);
	}
	write(2, "Error: Pointer not managed by GC.\n", 34);
	gc_cleanup(gcl);
	exit(EXIT_FAILURE);
}
