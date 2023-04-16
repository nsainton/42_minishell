/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:45:03 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/16 10:10:15 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gcmalloc(size_t size)
{
	void	*ptr;
	t_gc	*collector;

	//EPRINT
	collector = getgc();
	if (! collector)
		return (NULL);
	ptr = malloc(size);
	//LPRINT
	if (! (ptr && gc_add(ptr)))
		return (ptr);
	free(ptr);
	return (NULL);
}

void	*gccalloc(size_t nmemb, size_t size)
{
	void	*ptr;
	t_gc	*collector;

	collector = getgc();
	if (! collector)
		return (NULL);
	ptr = ft_calloc(nmemb, size);
	if (! (ptr && gc_add(ptr)))
		return (ptr);
	free(ptr);
	return (NULL);
}

void	*gcrealloc(void *pointer, size_t old_size, size_t new_size)
{
	void	*ptr;
	t_gc	*collector;

	collector = getgc();
	if (! collector)
		return (NULL);
	ptr = ft_realloc(pointer, old_size, new_size);
	if (! (ptr && gc_replace(pointer, ptr)))
		return (ptr);
	free(ptr);
	return (NULL);
}
