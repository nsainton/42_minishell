/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainto <nsainton@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:34:15 by nsainto           #+#    #+#             */
/*   Updated: 2023/08/23 10:34:45 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Arbitrary size to sort the array on the stack
	Here is recalled the functionning of insertion (which has
	a worst case complexity of O(n^2) and a best case complexity of O(n))
	We iterate through the elements of our array and for each i in A[2:n]
	we insert A[i] in the sorted array A[1..i-1].
	To do so we compare our element to the elements before it and check
	if they are sorted or no. 
	To insert our element, we move the number of elements we need one
	position forward to leave a slot available for the element we want
	to insert
	In the original version, it is an integer that is used and can thus
	reach -1 to signal that the element should be inserted at the beginning
	of the array.
	In this version, such thing is impossible because the length of our array
	is stored as a size_t. However, we make a last comparison to ensure that we
	don't miss the minimum if that is the elemen't we're looking at
*/
int	insertion_sort_tab(struct s_tab *tab, int (*cmp)())
{
	size_t	i;
	size_t	j;
	char	tmp[300];

	if (tab->len < 1)
		return (0);
	if (tab->elemsize > 300)
		return (1);
	i = 1;
	while (i < tab->len)
	{
		ft_memcpy(tmp, tab->tab + i * tab->elemsize, tab->elemsize);
		j = i - 1;
		while (j && cmp(tab->tab + i * tab->elemsize, \
		tab->tab + j * tab->elemsize) < 0)
			j --;
		if (j || cmp(tab->tab + i * tab->elemsize, \
		tab->tab + j * tab->elemsize) >= 0)
			j ++;
		ft_memmove(tab->tab + (j + 1) * tab->elemsize, \
		tab->tab + j * tab->elemsize, (i - j) * tab->elemsize);
		ft_memcpy(tab->tab + j * tab->elemsize, tmp, tab->elemsize);
		i ++;
	}
	return (0);
}
