/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:45:03 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/13 11:52:10 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gcmalloc(size_t size)
{
	void	*ptr;
	t_gc	*collector;
	int		error;

	collector = getgc();
	if (! collector)
		return (NULL);
	ptr = malloc(size);
	if (! (ptr && gc_add(ptr)))
		return (ptr);
	free(ptr);
	return (NULL);
}
