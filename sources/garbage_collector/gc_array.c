/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:05:03 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 16:20:28 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_size(void **array, t_csizet size)
{	
	size_t	index;

	index = 0;
	while (index < size)
	{
		free_node(*(array + index));
		index ++;
	}
	free_node(array);
}

void	free_array_null(void **array)
{
	size_t	index;

	index = 0;
	while (*(array + index))
	{
		free_node(*(array + index));
		index ++;
	}
	free_node(array);
}
