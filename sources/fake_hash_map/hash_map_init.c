/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:28:42 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 10:17:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_hashmap	*getmap(size_t (*hash_function)(const void *), \
void (*del)(void *))
{
	static struct s_hashmap	map;

	if (! (hash_function && del) || map.map)
		return (&map);
	map.map = gccalloc(MAP_SIZE, sizeof * map.map);
	if (! map.map)
		return (NULL);
	map.hash_function = hash_function;
	map.del = del;
	map.on_heap = 0;
	return (&map);
}
