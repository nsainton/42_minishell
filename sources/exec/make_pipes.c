/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:43 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 12:10:23 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipes(struct s_ncommand *commands)
{
	size_t	len;
	size_t	i;
	int		pipefd[2];

	len = tablen(commands, sizeof * commands);
	i = 0;
	while (i < len)
	{
		if (s_pipe(pipefd))
		{
			clear_fdlist();
			return (1);
		}
		(commands + i)->output_fd = pipefd[1];
		(commands + i + 1)->input_fd = pipefd[0];
		i ++;
	}
	return (0);
}
