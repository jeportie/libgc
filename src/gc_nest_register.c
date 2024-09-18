/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_nest_register.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:23:33 by jeportie          #+#    #+#             */
/*   Updated: 2024/07/08 00:47:39 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	gc_nest_register(void *ptr)
{
	t_gc_node	*new_node;
	void		**array;

	if (!ptr)
		return ;
	array = (void **)ptr;
	while (*array)
	{
		gc_register(*array);
		array++;
	}
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->is_marked = false;
	new_node->is_locked = false;
	new_node->is_array = true;
	new_node->fd = -1;
	new_node->temp_file = NULL;
	new_node->next = g_garbage_collector.head;
	g_garbage_collector.head = new_node;
}
