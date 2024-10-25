/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:59:04 by jeportie          #+#    #+#             */
/*   Updated: 2024/10/25 08:59:35 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

void gc_free(void *ptr, t_gc *gcl)
{
    t_gc_node *current = gcl->head;
    t_gc_node *prev = NULL;

    while (current)
    {
        if (current->ptr == ptr)
        {
            if (prev)
                prev->next = current->next;
            else
                gcl->head = current->next;
            free(current->ptr);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    write(2, "Error: Pointer not managed by GC.\n", 34);
    gc_cleanup(gcl);
    exit(EXIT_FAILURE);
}
