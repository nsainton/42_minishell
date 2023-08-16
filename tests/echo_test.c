/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:16:05 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/16 10:28:11 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	int	err;

	if (! argc)
	{
		printf("No prog name my G\n");
		exit(1);
	}
	err = echo((const char **)argv + 1, NULL);
	ft_printf("echo builtin returned : %d\n", err);
	return (0);
}
