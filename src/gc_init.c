/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:15:11 by jeportie          #+#    #+#             */
/*   Updated: 2025/02/10 15:43:18 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libgc.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*mem_src;

	mem_src = (unsigned char *)s;
	while (n--)
		*mem_src++ = (unsigned char)c;
	return (s);
}

void	gc_init(void)
{
	ft_memset(&g_gcl, 0, sizeof(t_gc));
}
