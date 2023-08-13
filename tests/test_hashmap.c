/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hashmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:25:47 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/13 10:16:33 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# ifndef MAP_SIZE
#  define MAP_SIZE 5
# endif

size_t	hash(const void *s)
{
	const char	*string;
	size_t		code;
	size_t		i;

	i = 0;
	code = 0;
	while (*(s + i))
	{
		code += *(s + i) * i;
		i ++;
	}
	return (code);
}

static int	add_map(const char *s)
{
	struct s_hashnmap	*map;
	char				*ns;

	map = getmap(NULL, NULL);
	if (! map->map)
		return (1);
	ns = gc_strdup(s);
	if (! ns)
		return (1);
	return (hash_map_add(map, ns));
}

static void	print_elem(void *elem)
{
	char	*str;

	str = (char *)elem;
	ft_printf("(%s)->");
}

static void	print_map(void (*print_func)(void *))
{
	struct s_hashmap	*map;
	size_t				i;

	map = getmap(NULL, NULL);
	if (! map->map)
		return ;
	i = 0;
	while (i < map->size)
	{
		ft_printf("-- %u --->", i);
		ft_lstiter(*(map + i), print_func);
		write(1, "\n", 1);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	struct s_hashmap	*map;
	struct s_list		*elem;
	int					i;

	map = getmap(hash, free_node);
	if (! map)
	{
		printf("Couldn't allocate\n");
		return (1);
	}
	i = 0;
	while (i < argc)
	{
		ft_printf("-----Before addition-----\n");
		print_map(print_elem);
		if (add_map(*(argv + i)))
		{
			printf("Error while adding : %s\n", *(argv + i));
			hash_map_clear(map);
			return (1);
		}
		ft_printf("------After addition------\n");
		print_map(print_elem);
		i ++;
	}
	i = 0;
	while (i < argc)
	{
		if (! (elem = hash_map_find(map, *(argv + i), ft_strcmp)))
		{
			printf("Error while retrieving : %s\n", *(argv + i));
			hash_map_clear(map);
			return (1);
		}
		ft_printf("I looked for : %s and found : %s\n", *(argv + i), *(char *)elem->content);
		ft_printf("-------Before deletion-------\n");
		print_map(print_elem);
		hash_map_delete(map, elem);
		ft_printf("-------After deletion--------\n");
		print_map(print_elem);
		i ++;
	}
	hash_map_clear(map);
	printf("Bonjour\n");
	return 0;
}
