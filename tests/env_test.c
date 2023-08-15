/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:36 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 09:37:30 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ansicolorcodes.h"
#include <unistd.h>
#include <stdio.h>
# define MSG "No mo mem bruv, can't reMEMber. Get it ?\nHahaha. Anyway \
see ya bruv"

extern char	**environ;

void	exit_message(int status, const char *message)
{
	char	*color;

	color = RED;
	if (! status)
		color = GRN;
	printf("%s%s%s\n", color, message, CRESET);
	exit_free_gc(status);
}

_Noreturn void	exit_free_gc(int status)
{
	free_gc();
	exit(status);
}

int	main(void)
{
	struct s_env	*environment;
	//char			**environ = {NULL};

	environment = create_env((const char **)environ);
	if (! environment)
		exit_message(1, MSG);
	printf("This is the env list\n");
	print_env(environment->env_list);
	printf("This is the export list\n");
	if (print_exportlist(environment->export_list))
		exit_message(1, MSG);
	exit_message(0, "Everything went great");
}
