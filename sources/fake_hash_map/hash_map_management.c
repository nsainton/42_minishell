/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:31:51 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 11:26:21 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_hash_index(const void *elem, \
size_t (*hash_function)(const void *), const size_t size)
{
	return (hash_function(elem) % size);
}

struct s_list	**get_hash_list(const struct s_hashmap *map, \
const void *elem)
{
	size_t	index;

	index = get_hash_index(elem, map->hash_function, map->size);
	return (map->map + index);
}

void	hash_map_delete(struct s_hashmap *map, struct s_list *elem)
{
	struct s_list	**elem_list;

	elem_list = get_hash_list(map, elem->content);
	if (! elem_list)
		return ;
	del_node(elem_list, elem, map->del);
}

void	hash_map_clear(struct s_hashmap *map)
{
	size_t	i;

	i = 0;
	while (i < map->size)
	{
		gc_lstclear(map->map + i, map->del);
		i ++;
	}
	free_node(map->map);
	if (map->on_heap)
		free_node(map);
}

int	hash_map_add(struct s_hashmap *map, void *elem)
{
	struct s_list	*node;

	node = gc_lstnew(elem);
	if (! node)
		return (1);
	ft_lstadd_front(get_hash_list(map, elem), node);
	return (0);
}
