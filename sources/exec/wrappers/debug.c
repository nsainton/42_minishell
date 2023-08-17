/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:39:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 11:11:14 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_fd(void *fd)
{
	ft_printf("This is the fd in the list : %d\n", *(int *)fd);
}

void	print_fdlist(void)
{
	struct s_list *list;

	EPRINT
	list = *get_fdlist();
	ft_lstiter(list, print_fd);
	LPRINT
}
