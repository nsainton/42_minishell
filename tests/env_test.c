/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:36 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 08:51:52 by nsainton         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	struct s_env	*environment;
	int				err;
	char			**null = {NULL};
	char			**environ = {NULL};

	if (! argc)
		exit_message(1, "No prog name bruv");
	environment = create_env((const char **)environ);
	if (! environment)
		exit_message(1, MSG);
	err = export((const char **)argv + 1, environment);
	if (err == ALLOCATION_ERROR)
		exit_message(1, MSG);
	ft_printf("export returned : %d\n", err);
	ft_printf("%s|||||||||||||||||||||||||||||||||||||||||||||||||PRINTING EXPORT LIST|||||||||||||||||||||||||||||||||||||||||||||||||||||%s\n", BLU, CRESET);
	if (export((const char **)null, environment))
		exit_message(1, MSG);
	ft_printf("This is the env list\n");
	env((const char **)environ, environment);
	err = unset((const char **)argv + 1, environment);
	ft_printf("unset returned : %d\n", err);
	ft_printf("%s|||||||||||||||||||||||||||||||||||||||||||||||||PRINTING EXPORT LIST|||||||||||||||||||||||||||||||||||||||||||||||||||||%s\n", YELB, CRESET);
	if (export((const char **)null, environment))
		exit_message(1, MSG);
	ft_printf("This is the env list\n");
	print_env(environment->env_list);
	env((const char **)environ, environment);
	ft_printf("TESTING FEATURES\n");
	env((const char **)argv + 1, environment);
	/*
	printf("This is the env list\n");
	print_env(environment->env_list);
	printf("This is the export list\n");
	*/
	/*
	if (print_exportlist(environment->export_list))
		exit_message(1, MSG);
	*/
	exit_message(0, "Everything went great");
}
