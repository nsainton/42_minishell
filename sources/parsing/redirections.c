/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:50:20 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/18 16:59:26 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	realloc_redirs(
t_redir	**get_redirections(char *line, size_t *len)
{
	size_t	index;
	size_t	length;
	size_t	tmp;
	t_redir	**redirections;

	index = 0;
	length = *len;
	while (index < length)
	{
		
