/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_mark_lock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:50:19 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/30 13:15:52 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	gc_mark(void *ptr)
{
	t_gc_node	*current;

	current = g_garbage_collector.head;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (current->is_marked)
				return ;
			current->is_marked = true;
			return ;
		}
		current = current->next;
	}
}

void	gc_lock(void *ptr)
{
	t_gc_node	*current;

	current = g_garbage_collector.head;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->is_locked = true;
			return ;
		}
		current = current->next;
	}
}

void	gc_nest_lock(void *ptr)
{
	int		i;
	void	**array;

	if (!ptr)
		return ;
	array = (void **)ptr;
	i = 0;
	while (array[i])
	{
		gc_lock(array[i]);
		i++;
	}
	gc_lock(ptr);
}

void	gc_unlock(void *ptr)
{
	t_gc_node	*current;

	current = g_garbage_collector.head;
	while (current)
	{
		if (current->ptr == ptr)
		{
			current->is_locked = false;
			return ;
		}
		current = current->next;
	}
}
