/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:43:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 16:33:25 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

t_list	*gc_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = ft_lstnew(content);
	if (! (new_elem && gc_add(new_elem)))
		return (new_elem);
	free(new_elem);
	return (NULL);
}

t_list	*gc_lstnew_cpy(t_cvoid *content, size_t size)
{
	t_list	*new_elem;
	void	*new_content;

	new_content = gcmalloc(size);
	if (! new_content)
		return (new_content);
	ft_memcpy(new_content, content, size);
	new_elem = gc_lstnew(new_content);
	if (! new_elem)
		free_nodes(1);
	return (new_elem);
}
