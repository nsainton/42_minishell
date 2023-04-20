/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:16:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/20 16:47:11 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
