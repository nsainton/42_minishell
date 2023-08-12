/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:26:09 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/12 12:03:57 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	struct s_hashmap
	{
		struct s_list	**map;
		size_t			size;
		size_t			(*hash_function)(const void *);
		void			(*del)(void *);
	};
*/

size_t	get_hash_index(const void *elem, size_t (*find_index)(const void *), \
const size_t size)
{
	return (find_index(elem) % size);
}

struct s_list	**get_hash_list(const struct s_hashmap *map, \
const void *elem)
{
	size_t	index;

	index = get_hash_index(elem, map->hash_function, map->size);
	return (map->map + map->index);
}

void	*hash_map_find(const struct s_hashmap *map, void *elem, \
int (*cmp)())
{
	struct s_list	**elem_list;
	struct s_list	*elem_in_list;

	elem_list = get_hash_list(map, elem);
	if (! elem_list)
		return (NULL);
	return (ft_list_find(*elem_list, elem, cmp));
}

void	hash_map_delete(struct s_hashmap *map, struct s_list *elem)
{
	struct s_list	**elem_list;

	elem_list = get_hash_list(map, elem);
	if (! elem_list)
		return (NULL);
	del_node(elem_list, elem, map->del);
}
