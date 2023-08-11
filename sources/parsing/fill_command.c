/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:23 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/11 14:18:41 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	decrypt_tab(char **tab)
{
	while (*tab)
	{
		decrypt_string(*tab);
		tab ++;
	}
}

static void	set_command_parameters(struct s_ncommand *command, \
struct s_tab *heredocs, struct s_tab *redirs)
{
	command->heredocs = (t_heredoc *)heredocs->tab;
	command->redirs = (t_redirection *)redirs->tab;
	command->output_fd = 1;
	command->input_fd = 0;
}

static int	fill_command(t_ncommand *command, char *line)
{
	t_tab	redirs;
	t_tab	heredocs;
	t_str	sline;
	char	**split;

	sline.str = line;
	sline.len = strlen(line);
	if (redirections(&redirs, &sline) || redirs_to_heredocs(&redirs, &heredocs))
		return (ALLOCATION_ERROR);
	split = gc_split(line, ' ');
	if (! split)
		return (ALLOCATION_ERROR);
	decrypt_tab(split);
	command->command = *split;
	if (command->command)
		command->args = split + 1;
	set_command_parameters(command, &heredocs, &redirs);
	return (NO_ERROR);
}

int	fill_commands(t_tab *command, char *line)
{
	t_ncommand	com;
	char		**commands;
	size_t		index;

	commands = gc_split(line, '|');
	ft_bzero(&com, sizeof com);
	if (! commands)
		return (ALLOCATION_ERROR);
	index = 0;
	while (*(commands + index))
	{
		if (fill_command(&com, *(commands + index)))
			return (ALLOCATION_ERROR);
		if (add_tab(command, &com))
			return (ALLOCATION_ERROR);
		index ++;
	}
	return (NO_ERROR);
}
