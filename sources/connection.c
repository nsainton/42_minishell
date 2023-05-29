/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:04:03 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/29 15:40:54 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	**get_tab_references(void *original, t_csizet elemsize, int *err)
{
	size_t	tablen;
	void	**tab;
	size_t	index;

	tablen = tablen(original, elemsize);
	if (! tablen)
		return (NULL);
	if (tablen == SIZE_MAX)
	{
		*err = 1;
		return (NULL);
	}
	tab = gccalloc(tablen + 1, sizeof *tab);
	if (! tab)
	{
		*err = 1;
		return (NULL);
	}
	index = 0;
	while (index < tablen)
	{
		*(tab + index) = original + index * elemsize;
		index ++;
	}
	return (tab);
}

static int	ncommand_to_command(t_ncommand *original, t_command **command)
{
	t_redirection	**redirs;
	t_heredoc		**heredocs;
	int				err;

	*command = gccalloc(1, sizeof **command);
	if (! command)
		return (ALLOCATION_ERROR);
	err = 0;
	redirs = get_tab_references(original->redirs, sizeof original->redirs, &err);
	if (! redirs && err)
		return (ALLOCATION_ERROR);
	heredocs = get_tab_references(original->heredocs, sizeof original->heredocs, &err);
	if (! heredocs && err)
		return (ALLOCATION_ERROR);
	(*command)->command = original->command;
	(*command)->args = original->args;
	(*command)->heredocs = heredocs;
	(*command)->redirs = redirs;
	return (NO_ERROR);
}

t_command	**get_commands_reference(t_ncommand *original)
{
	t_command	**commands;
	size_t		tablen;
	size_t		index;

	tablen = tablen(original, elemsize);
	if (! tablen || tablen == SIZE_MAX)
		return (NULL);
	commands = gccalloc(tablen + 1, sizeof *commands);
	if (! commands)
		return (NULL);
	index = 0;
	while (index < tablen)
	{
		if (ncommand_to_command(original + index, commands + index))
			return (NULL);
		index ++;
	}
	return (commands);
}
