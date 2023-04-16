/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:05:03 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/16 12:29:56 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_array_strings(char **array, t_csizet size, t_cint errcode)
{	
	size_t	index;
	int		error;

	index = 0;
	error = 0;
	while (index < size)
	{
		error = free_node(*(array + index), errcode);
		if (error == NOT_IN_COLLECTOR || error == NO_COLLECTOR)
			return (error);
		index ++;
	}
	return (free_node(array, errcode));
}
