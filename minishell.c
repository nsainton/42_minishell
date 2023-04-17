/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/17 14:35:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_strings_array(t_csizet size)
{
	char	**array;
	size_t	index;

	if (! (array = gccalloc(size, sizeof * array)))
		return (NULL);
	index = 0;
	while (index < size)
	{
		if (! (*(array + index) = gccalloc(1, sizeof ** array)))
			return (NULL);
		index ++;
	}
	return (array);
}

void	print_array(char *const*array, t_csizet size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		ft_printf("array[%u] : %p\n", index, *(array + index));
		index ++;
	}
	ft_printf("array : %p\n", array);
}

static void print_strings(char *const *array)
{
	size_t	index;

	ft_printf("This is the strings array address : %p\n", array);
	index = 0;
	while (*(array + index))
	{
		ft_printf("array[%u] : %s\n", index, *(array + index));
		index ++;
	}
}

int	main(int ac, char **av)
{
	/*
	char	*line;
	char	**strings_array;
	void	*node;
	void	*rnode;
	*/
	char	**split;

	//sigaction(SIGINT, sig_handler);
	/*
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			break ;
		printf("%s\n", line);
		//parse_line(line);
	}
	*/
	/*
	for (size_t index = 0; index < 10 * TRASH_SIZE + 10; index ++)
	{
		line = gcmalloc(1);
		if (! line)
			break ;
		if (index == 3)
			node = line;
		if (index == 5)
			rnode = line;
		if (index == 20 && (! (strings_array = allocate_strings_array(index))))
			return (free_gc(EXIT_FAILURE));
	}
	ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	int error = free_nodes(10, 0);
	if (error)
		ft_printf("This is the error : %d\n", error);
	else
		ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	ft_printf("This is the saved node :%p\n", node);
	free_node(node, 0);
	print_collector();
	ft_printf("This is the node to realloc : %p\n", rnode);
	rnode = gcrealloc(rnode, 1, 3);
	ft_printf("This is the realloced' node : %p\n", rnode);
	if (! rnode)
		return (free_gc(NOT_IN_COLLECTOR));
	print_collector();
	print_array(strings_array, 20);
	free_array_strings_size(strings_array, 20, 0);
	print_collector();
	*/
	if (ac < 3)
		return (NO_ERROR);
	print_collector();
	split = gc_split(av[1], **(av + 2));
	print_collector();
	if (! split)
		return (free_gc(ALLOCATION_ERROR));
	print_strings(split);
	return (free_gc(0));
}
