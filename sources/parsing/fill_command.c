/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:23 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 13:53:13 by nsainton         ###   ########.fr       */
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


int	fill_command(t_command *command, char *line)
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
	command->args = split + 1;
	command->heredocs = (t_heredoc *)heredocs.tab;
	command->redirs = (t_redirection *)redirs.tab;
	free_node(line);
	return (NO_ERROR);
}
