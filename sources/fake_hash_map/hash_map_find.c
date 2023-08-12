/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:26:09 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/12 12:34:29 by nsainton         ###   ########.fr       */
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
		int				on_heap;
	};
*/

struct s_list	*hash_map_find(const struct s_hashmap *map, void *elem, \
int (*cmp)())
{
	struct s_list	**elem_list;

	elem_list = get_hash_list(map, elem);
	if (! elem_list)
		return (NULL);
	return (ft_list_find(*elem_list, elem, cmp));
}
