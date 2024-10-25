/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:55:40 by jeportie          #+#    #+#             */
/*   Updated: 2024/10/25 13:09:19 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	*gc_realloc(void *ptr, size_t size, t_gc *gcl)
{
	t_gc_node	*current;
	void		*new_ptr;
	size_t		old_size;
	size_t		copy_size;

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
		current = current->next;
	}
	write(2, "Error: Pointer not managed by GC.\n", 34);
	gc_cleanup(gcl);
	exit(EXIT_FAILURE);
}
