/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:16:35 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 11:54:13 by nsainton         ###   ########.fr       */
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
	int				err;
	struct s_env	*environment;
	//char			**environ = {NULL};

	if (! argc)
		exit_message(1, "No program name bruv");
	environment = create_env((const char **)environ);
	if (! environment)
		exit_message(1, MSG);
	err = cd((const char **)argv + 1, environment);
	ft_printf("cd returned : %d\n", err);
	err = pwd((const char **)argv + 1);
	ft_printf("pwd returned : %d\n", err);
	exit_message(0, "Ol good my G");
}
