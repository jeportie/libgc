/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_fd_register.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:18:49 by jeportie          #+#    #+#             */
/*   Updated: 2025/02/10 15:46:24 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	gc_fd_register(int fd)
{
	t_gc_node	*new_node;

	if (fd <= -1)
		return ;
	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
	{
		gc_cleanup();
		write(2, "Error: GC node malloc failed.\n", 31);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = NULL;
	new_node->size = 0;
	new_node->is_marked = false;
	new_node->is_locked = true;
	new_node->is_array = false;
	new_node->fd = fd;
	new_node->temp_file = NULL;
	new_node->next = g_gcl.head;
	g_gcl.head = new_node;
}
