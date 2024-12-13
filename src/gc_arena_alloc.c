/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_arena_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:57:36 by jeportie          #+#    #+#             */
/*   Updated: 2024/12/13 16:23:34 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

static inline size_t	gc_align_up(size_t size, size_t alignment)
{
	return ((size + alignment - 1) & ~(alignment - 1));
}

int	gc_init_arena(t_gc *gcl)
{
	t_arena_node	*new_arena;

	new_arena = malloc(sizeof(t_arena_node));
	if (!new_arena)
	{
		write(2, "Arena node allocation failed.\n", 31);
		gc_cleanup(gcl);
		exit(EXIT_FAILURE);
	}
	new_arena->arena_capacity = DEFAULT_ARENA_SIZE;
	new_arena->arena_base = malloc(new_arena->arena_capacity);
	if (!new_arena->arena_base)
	{
		write(2, "Arena memory allocation failed.\n", 33);
		free(new_arena);
		gc_cleanup(gcl);
		exit(EXIT_FAILURE);
	}
	new_arena->arena_offset = 0;
	new_arena->id = gcl->next_arena_id++;
	new_arena->next = gcl->a_head;
	gcl->a_head = new_arena;
	return (new_arena->id);
}

void	*gc_arena_alloc(size_t size, int id, t_gc *gcl)
{
	t_arena_node	*arena;
	t_arena_node	*new_arena;
	size_t			arena_capacity;
	size_t			aligned_offset;
	size_t			new_offset;
	void			*ptr;

	arena = gcl->a_head;
	new_arena = NULL;
	while (arena && arena->id != id)
	{
		arena = arena->next;
	}
	if (!arena)
	{
		write(2, "Error: Arena not found.\n", 24);
		gc_cleanup(gcl);
		exit(EXIT_FAILURE);
	}
	arena_capacity = DEFAULT_ARENA_SIZE;
	if (size > arena_capacity)
	{
		arena_capacity = gc_align_up(size, ALIGNMENT);
	}
	aligned_offset = gc_align_up(arena->arena_offset, ALIGNMENT);
	new_offset = aligned_offset + size;
	if (new_offset > arena->arena_capacity)
	{
		new_arena = malloc(sizeof(t_arena_node));
		if (!new_arena)
		{
			write(2, "Failed to create new arena.\n", 28);
			gc_cleanup(gcl);
			exit(EXIT_FAILURE);
		}
		new_arena->arena_capacity = arena_capacity;
		new_arena->arena_base = malloc(new_arena->arena_capacity);
		if (!new_arena->arena_base)
		{
			write(2, "Arena memory allocation failed.\n", 33);
			free(new_arena);
			gc_cleanup(gcl);
			exit(EXIT_FAILURE);
		}
		new_arena->arena_offset = 0;
		new_arena->id = id;
		new_arena->next = gcl->a_head;
		gcl->a_head = new_arena;
		arena = new_arena;
		aligned_offset = gc_align_up(arena->arena_offset, ALIGNMENT);
		new_offset = aligned_offset + size;
		if (new_offset > arena->arena_capacity)
		{
			write(2, "Unexpected arena allocation error.\n", 35);
			gc_cleanup(gcl);
			exit(EXIT_FAILURE);
		}
	}
	ptr = (char *)arena->arena_base + aligned_offset;
	arena->arena_offset = new_offset;
	return (ptr);
}

void	gc_collect_arena(int id, t_gc *gcl)
{
	t_arena_node	*current;
	t_arena_node	*prev;
	t_arena_node	*to_free;

	current = gcl->a_head;
	prev = NULL;
	to_free = NULL;
	while (current)
	{
		if (current->id == id)
		{
			if (prev)
				prev->next = current->next;
			else
				gcl->a_head = current->next;
			free(current->arena_base);
			to_free = current;
			current = current->next;
			free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
