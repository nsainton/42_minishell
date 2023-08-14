/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:36 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/14 12:44:37 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

//extern char	**environ;

void	exit_free_gc(int status)
{
	free_gc();
	exit(status);
}

int	main(void)
{
	struct s_env	*environment;
	char			**environ = {NULL};

	environment = create_env((const char **)environ);
	if (! environment)
	{
		printf("SORRY bruv, unknown problem\nC ya bruv\n");
		exit(1);
	}
	printf("This is the env list\n");
	print_env(environment->env_list);
	printf("This is the export list\n");
	print_env(environment->export_list);
	exit_free_gc(0);
}
