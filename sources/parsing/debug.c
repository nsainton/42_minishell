/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:16:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 13:09:34 by nsainton         ###   ########.fr       */
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

void	print_redirs(t_redirection *redirs, size_t len)
{
	size_t	index;

	index = 0;
	while (index++ < len)
		print_redir(redirs + index - 1, index);
}
