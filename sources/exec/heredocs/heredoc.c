/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:33:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/08 17:19:31 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Comparison array nullelem is of size 20 to not allocate it and to 
	ensure the portability in case size of `int` increases in the future
	nullelem array work with this function for a sizeof int up to 10 bytes
*/
static void	init_list(int *descriptors_list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(descriptors_list + i) = -1;
		i ++;
	}
}

static int	match_fds(int *descriptors_list)
{
	char	nullelem[20];
	size_t	i;

	ft_bzero(nullelem, 2 * sizeof * descriptors_list);
	i = 0;
	while (ft_memcmp(descriptors_list + i, nullelem, \
	2 * sizeof * descriptors_list) && *(descriptors_list + i) != -1)
	{
		if (dup2(*(descriptors_list + i + 1), *(descriptors_list + i)) == -1)
		{
			perror("dup2");
			clear_list();
			return (1);
		}
		if (close(*(descriptors_list + i + 1)))
		{
			*(descriptors_list + i + 1) = -1;
			clear_list();
			return (1);
		}
		*(descriptors_list + i + 1) = *(descriptors_list + i);
		i += 2;
	}
	return (0);
}

int	heredoc(const struct s_command *command, const struct s_env *env)
{
	size_t	len;
	int		*descriptors_list;

	if (! *command->heredocs)
		return (EXIT_SUCCESS);
	len = tablen(*command->heredocs, sizeof **command->heredocs);
	if (! len)
		return (EXIT_SUCCESS);
	descriptors_list = getlist(len + 1, 2 * sizeof * descriptors_list);
	if (! descriptors_list)
		return (1);
	init_list(descriptors_list, 2 * len);
	if (get_heredocs(descriptors_list, command, env, len) || \
	match_fds(descriptors_list))
		return (1);
	init_sigs();
	return (EXIT_SUCCESS);
}
