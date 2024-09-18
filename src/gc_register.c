/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:25:20 by jeportie          #+#    #+#             */
/*   Updated: 2024/07/08 01:24:00 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	gc_register(void *ptr)
{
	t_gc_node	*new_node;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->is_marked = false;
	new_node->is_locked = false;
	new_node->is_array = false;
	new_node->fd = -1;
	new_node->temp_file = NULL;
	new_node->next = g_garbage_collector.head;
	g_garbage_collector.head = new_node;
}

void	gc_temp_file_register(const char *filename)
{
	t_gc_node	*new_node;

	if (!filename)
		return ;
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return ;
	new_node->ptr = NULL;
	new_node->is_marked = false;
	new_node->is_locked = true;
	new_node->is_array = false;
	new_node->fd = -1;
	new_node->temp_file = ft_strdup(filename);
	if (!new_node->temp_file)
	{
		free(new_node);
		return ;
	}
	gc_register(new_node->temp_file);
	gc_lock(new_node->temp_file);
	new_node->next = g_garbage_collector.head;
	g_garbage_collector.head = new_node;
}
