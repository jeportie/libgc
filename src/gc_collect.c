/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:23:26 by jeportie          #+#    #+#             */
/*   Updated: 2025/02/10 15:45:07 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"
#include <stdarg.h>

static void	gc_delete_node(t_gc_node **prev, t_gc_node **current)
{
	t_gc_node	*next_node;

	next_node = (*current)->next;
	if (*prev)
		(*prev)->next = next_node;
	else
		g_gcl.head = next_node;
	if ((*current)->ptr)
		free((*current)->ptr);
	free(*current);
	*current = next_node;
}

void	gc_collect(void)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	current = g_gcl.head;
	prev = NULL;
	while (current)
	{
		if (!current->is_marked && !current->is_locked)
			gc_delete_node(&prev, &current);
		else
		{
			current->is_marked = false;
			prev = current;
			current = current->next;
		}
	}
}
