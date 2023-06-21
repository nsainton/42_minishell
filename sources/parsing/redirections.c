/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:50:20 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/21 22:29:15 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	push_redirection(t_tab *redirs, t_str *line, t_csizet index, int fd)
{
	t_redirection	redir;
	size_t			begredir;
	size_t			nextspace;

	/*
	EPRINT
	ft_printf("This is my pid : %d\n", getpid());
	*/
	ft_bzero(&redir, sizeof redir);
	begredir = find_next(line->str, index, "<>");
	/*
	ft_printf("This is begredir : %u\n", begredir);
	ft_printf("This is the char : %c\n", *(line->str + begredir));
	*/
	redir.mode = find_mode(line->str, begredir);
	/*
	ft_printf("Mode found : %c\n", redir.mode);
	ft_printf("This is the input file descriptor : %d\n", fd);
	*/
	if (fd != -1)
		redir.fd = fd;
	else if (redir.mode == 'a' || redir.mode == 'w')
	{
		//ft_printf("This is the mode : %c\n", redir.mode);
		redir.fd = 1;
		//ft_printf("This is the file descriptor : %d\n", redir.fd);
	}
	while (*(line->str + begredir) == '<' || *(line->str + begredir) == '>')
		begredir ++;
	//ft_printf("Start from : %c\n", *(line->str + begredir));
	nextspace = find_next(line->str, begredir + 1, "<> ");
	redir.file = gc_substr(line->str, begredir, nextspace - begredir);
	if (! redir.file)
		return (ALLOCATION_ERROR);
	decrypt_string(redir.file);
	/*
	ft_printf("This is the file : %s\n", redir.file);
	ft_printf("This is the line at first : %s\n", line->str + index);
	ft_printf("Nextspace : %u -- Index : %u\n", nextspace, index);
	ft_printf("Line_len : %u\n", line->len);
	ft_printf("Number to move : %u\n", line->len + 1 - nextspace);
	*/
	ft_memmove(line->str + index, line->str + nextspace\
	, line->len + 1 - nextspace);
	line->len -= (nextspace - index);
	/*
	ft_printf("And then : %s\n", line->str + index);
	LPRINT
	*/
	return (add_tab(redirs, &redir));
}
/*
This function assumes that for example if the line is "echo bonjour >salut"
then index points to the '>'
thus ft_printf("%s\n", line + index) would print : >salut
*/
static int	add_redirection(t_tab *redirs, t_str *line, t_csizet index)
{
	int				err;
	int				fd;
	size_t			space;

	/*
	EPRINT
	ft_printf("This is the remaining : %s\n", line->str + index);
	ft_printf("This is the index : %u\n", index);
	*/
	space = find_prev(line->str, index, " ");
	err = 0;
	//ft_printf("This is the line : %s\n", line->str);
	if (index > space + 1)
	{
		/*
		ft_printf("This is what we are looking at : ");
		putnstr(line->str + space + 1, index - space - 1, 1);
		ft_putchar_fd('\n', 1);
		*/
		fd = atoi_until(line->str + space + 1, DEC, &err, index - space - 1);
	}
	else
		fd = -1;
	if (fd < 0 || err)
		return (push_redirection(redirs, line, index, -1));
	else
		return (push_redirection(redirs, line, space + 1, fd));
	return (UNKNOWN_ERROR);
}

int	redirections(t_tab *redirs, t_str *line)
{
	size_t	index;

	if (allocate_tab(redirs, REDIRS_SIZE, sizeof (t_redirection)))
		return (ALLOCATION_ERROR);
	index = 0;
	while (index < line->len)
	{
		if ((*(line->str + index) == '>' || *(line->str + index) == '<'))
		{
			if (add_redirection(redirs, line, index))
				return (ALLOCATION_ERROR);
		}
		else
			index ++;
	}
	if (redirs->len == redirs->size && realloc_tab(redirs, redirs->size + 1))
		return (ALLOCATION_ERROR);
	return (NO_ERROR);
}

int	redirs_to_heredocs(t_tab *redirs, t_tab *heredocs)
{
	t_redirection	*reds;
	t_heredoc		hd;
	size_t			index;
	//char			memory[300];

	//EPRINT
	//ft_bzero(memory, sizeof memory);
	if (allocate_tab(heredocs, REDIRS_SIZE, sizeof (t_heredoc)))
		return (ALLOCATION_ERROR);
	reds = (t_redirection *)redirs->tab;
	//print_redirs(reds);
	index = 0;
	ft_bzero(&hd, sizeof hd);
	//ft_printf("This is the redirs len : %u\n", redirs->len);
	while (index < redirs->len)
	{
		if ((reds + index)->mode == 'h')
		{
			//print_redir(reds + index, index + 1);
			hd.fd = (reds + index)->fd;
			hd.limiter = (reds + index)->file;
			if (add_tab(heredocs, &hd))
				return (ALLOCATION_ERROR);
			ft_memmove(reds + index, reds + index + 1, sizeof * reds * (redirs->len - index));
			//print_tab_bin(heredocs);
			//ft_printf("Printed\n");
			//print_heredoc(heredocs->tab + (heredocs->len - 1) * heredocs->elemsize, heredocs->len);
			redirs->len -= 1;
		}
		else
			index ++;
	}
	if (heredocs->len == heredocs->size && realloc_tab(heredocs, heredocs->size + 1))
		return (ALLOCATION_ERROR);
	return (NO_ERROR);
}
