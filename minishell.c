/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:08:42 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/13 19:13:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

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
	}
	ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	int error = free_nodes(gc_len() / 2, 0);
	if (error)
		ft_printf("This is the error : %d\n", error);
	else
		ft_printf("This is the len : %u\n", gc_len());
	print_collector();
	free_gc(0);
	return (0);
}
