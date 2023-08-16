/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stds_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:07:18 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 10:40:04 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	int	i;
	int	fd;
	int	err;

	if (argc < 2)
	{
		printf("Yo bruv, gimme some fds\nMotherfu****\n");
		return (1);
	}
	i = 1;
	err = 0;
	while (i < argc)
	{
		fd = ft_atoi(*(argv + i));
		i ++;
		if (fd < -2)
			continue ;
		if (save_stds(fd))
		{
			ft_printf("Big error bruv\n");
			err = 1;
			break ;
		}
	}
	clear_fdlist();
	free_gc();
	return (err);
}
