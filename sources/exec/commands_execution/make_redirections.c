/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:47:59 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/12 09:54:01 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>

/**
* @brief Makes the redirections for the given command
*
* @params[in] command : A struct s_ncommand variable that holds the command
* we are looking at.
*
* @return An integer that is null if everything went well and that 
* is positive otherwise
*/

static int	get_flags(const int mode)
{
	if (mode == 'b')
		return (O_RDWR | O_CREAT | O_TRUNC);
	if (mode == 'r')
		return (O_RDONLY);
	if (mode == 'a')
		return (O_WRONLY | O_APPEND | O_CREAT);
	if (mode == 'w')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	return (0);
}

/*
	In the struct s_redir structure there is a integer, a char and a
	char pointer. Even admitting that those would be padded to align with
	the addresses of 3 char pointers, the full size of struct s_redir
	would be at most 30 bytes.
*/
int	make_redirections(struct s_ncommand *command)
{
	size_t			i;
	char			nullelem[30];
	int				fd;
	struct s_redir	*redir;

	if (! command->redirs)
		return (0);
	ft_bzero(nullelem, sizeof *command->redirs);
	i = 0;
	while (ft_memcmp(nullelem, command->redirs + i, sizeof *command->redirs))
	{
		redir = command->redirs + i;
		fd = s_open(redir->file, get_flags(redir->mode), 0644);
		if (! fd)
			return (1);
		ft_printf("The file %s is opened on fd %d\n", redir->file, fd);
		if ((s_dup2(fd, redir->fd) == -1)|| s_close(fd))
			return (1);
		ft_printf("fd %d has been duplicated on fd %d and closed\n", fd, redir->fd);
		i ++;
	}
	return (0);
}
