/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:55:40 by jeportie          #+#    #+#             */
/*   Updated: 2024/10/25 08:57:39 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

static void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char       *d;
    const unsigned char *s;

    if (!dest || !src)
        return NULL;
    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    while (n--)
        *d++ = *s++;
    return dest;
}

void *gc_realloc(void *ptr, size_t size, t_gc *gcl)
{
    t_gc_node *current;
    void *new_ptr;
    size_t old_size;

    if (!ptr)
        return gc_malloc(size, gcl);
    if (size == 0)
    {
        gc_free(ptr, gcl);
        return NULL;
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
            size_t copy_size = (old_size < size) ? old_size : size;
            ft_memcpy(new_ptr, ptr, copy_size);
            free(current->ptr);
            current->ptr = new_ptr;
            current->size = size;
            return new_ptr;
        }
        current = current->next;
    }
    write(2, "Error: Pointer not managed by GC.\n", 34);
    gc_cleanup(gcl);
    exit(EXIT_FAILURE);
}
