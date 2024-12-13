/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:09:32 by jeportie          #+#    #+#             */
/*   Updated: 2024/12/13 17:22:30 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	gc_cleanup(t_gc *gcl)
{
	t_gc_node		*current;
	t_gc_node		*next;
	t_arena_node	*a_current;
	t_arena_node	*a_next;

	current = gcl->head;
	while (current)
	{
		next = current->next;
		if (current->temp_file)
			unlink(current->temp_file);
		if (current->fd > -1)
			close(current->fd);
		else if (current->ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		free(current);
		current = next;
	}
	gcl->head = NULL;
	a_current = gcl->a_head;
	while (a_current)
	{
		a_next = a_current->next;
		free(a_current->arena_base);
		a_current->arena_base = NULL;
		free(a_current);
		a_current = a_next;
	}
	gcl->a_head = NULL;
	free(gcl);
	gcl = NULL;
}
