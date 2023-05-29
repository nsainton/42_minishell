/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:16:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/28 12:44:01 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_line(t_metachar *mc, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		ft_printf("%c-%u:", (mc + index)->c, (mc + index)->state);
		index ++;
	}
	ft_printf("\n");
}
*/

void	print_redir(t_redirection *redir, size_t no)
{
	ft_printf("-----------------Redirection number %u-------------------\n", no);
	ft_printf("File descriptor : %d\n", redir->fd);
	ft_printf("Mode : %c\n", redir->mode);
	ft_printf("File : %s\n", redir->file);
	ft_printf("---------------------------------------------------------\n");
}

void	print_redirs(t_redirection *redirs)
{
	size_t	index;
	char	null[200];

	index = 0;
	if (! redirs)
		return ;
	ft_bzero(null, 200);
	while (ft_memcmp(redirs + index, null, sizeof *redirs))
	{
		print_redir(redirs + index, index + 1);
		index ++;
	}
}

void	print_args(char **args)
{
	size_t	index;

	index = 0;
	if (! args)
		return ;
	while (*(args + index))
	{
		ft_printf("Argument[%u] : %s\n", index, *(args + index));
		index ++;
	}
}

void	print_heredoc(t_heredoc *heredoc, size_t no)
{
	ft_printf("--------------------Heredoc number %u---------------------\n", no);
	ft_printf("File descriptor : %d\n", heredoc->fd);
	ft_printf("Limiter : %s\n", heredoc->limiter);
	ft_printf("---------------------------------------------------------\n");
}

void	print_heredocs(t_heredoc *heredoc)
{
	size_t	index;
	char	null[200];

	index = 0;
	if (! heredoc)
		return ;
	ft_bzero(null, 200);
	while (ft_memcmp(heredoc + index, null, sizeof * heredoc))
	{
		print_heredoc(heredoc + index, index + 1);
		index ++;
	}
}

void	print_command(t_command *command, size_t no)
{
	ft_printf("---------------Command number %u-------------------------\n", no);
	ft_printf("Command : %s\n", command->command);
	print_args(command->args);
	print_redirs(command->redirs);
	print_heredocs(command->heredocs);
}

void	print_commands(t_command *commands)
{
	size_t	index;
	char	null[200];

	index = 0;
	ft_bzero(null, 200);
	while (ft_memcmp(commands + index, null, sizeof * commands))
	{
		print_command(commands + index, index + 1);
		index ++;
	}
}
