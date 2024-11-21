/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:25:20 by jeportie          #+#    #+#             */
/*   Updated: 2024/11/20 15:40:01 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	gc_register(void *ptr, t_gc *gcl)
{
	t_gc_node	*new_node;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		gc_cleanup(gcl);
		write(2, "Error: GC node malloc failed.\n", 31);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->size = 0;
	new_node->is_marked = false;
	new_node->is_locked = false;
	new_node->is_array = false;
	new_node->fd = -1;
	new_node->temp_file = NULL;
	new_node->next = gcl->head;
	gcl->head = new_node;
}

static t_gc_node	*init(t_gc_node *new_node, const char *filename, t_gc *gcl)
{
	new_node->ptr = NULL;
	new_node->size = 0;
	new_node->is_marked = false;
	new_node->is_locked = true;
	new_node->is_array = false;
	new_node->fd = -1;
	new_node->temp_file = gc_strdup(filename, gcl);
	return (new_node);
}

void	gc_temp_file_register(const char *filename, t_gc *gcl)
{
	t_gc_node	*new_node;

	if (!filename)
		return ;
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		gc_cleanup(gcl);
		write(2, "Error: GC node malloc failed.\n", 31);
		exit(EXIT_FAILURE);
	}
	init(new_node, filename, gcl);
	if (!new_node->temp_file)
	{
		free(new_node);
		gc_cleanup(gcl);
		write(2, "Error: GC node malloc failed.\n", 31);
		exit(EXIT_FAILURE);
	}
	gc_register(new_node->temp_file, gcl);
	gc_lock(new_node->temp_file, gcl);
	new_node->next = gcl->head;
	gcl->head = new_node;
}
