/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/16 09:56:45 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	void	*node;
	void	*rnode;

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
	for (int index = 0; index < TRASH_SIZE + 10; index ++)
	{
		line = gcmalloc(1);
		if (! line)
			break ;
		if (index == 3)
			node = line;
		if (index == 5)
			rnode = line;
	}
	ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	int error = free_nodes(gc_len() / 2, 0);
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
	return (free_gc(0));
}
