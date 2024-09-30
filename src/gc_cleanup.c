/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:09:32 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/30 13:15:02 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void	gc_cleanup(void)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = g_garbage_collector.head;
	while (current)
	{
		next = current->next;
		if (current->temp_file)
			unlink(current->temp_file);
		if (current->fd > -1)
			close(current->fd);
		else if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	g_garbage_collector.head = NULL;
}
