/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:43 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 13:41:38 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipes(struct s_ncommand *commands)
{
	size_t	len;
	size_t	i;
	int		pipefd[2];

	len = tablen(commands, sizeof * commands);
	ft_printf("This is the len : %u\n", len);
	if (len < 2)
		return (0);
	i = 0;
	while (i < len - 1)
	{
		if (s_pipe(pipefd))
			return (1);
		(commands + i)->output_fd = pipefd[1];
		(commands + i + 1)->input_fd = pipefd[0];
		i ++;
	}
	return (0);
}
