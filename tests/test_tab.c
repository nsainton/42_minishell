/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:36:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/14 10:03:58 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#define MSG "No mo mem bruv, can't reMEMber. Hahaha\nSee ya bruv"

_Noreturn void exit_error(const char *message, int error)
{
	printf("%s\n", message);
	free_gc();
	exit(error);
}

static void	tab_iter(const struct s_tab *tab, void (*func)())
{
	size_t	i;
	void	*mem;

	i = 0;
	mem = tab->tab;
	while (i < tab->len)
	{
		func(mem + i * tab->elemsize);
		i ++;
	}
}

void	print_string(const char *s)
{
	printf("%s\n", s);
}

int	main(int argc, char **argv)
{
	struct s_tab	tab;
	size_t			index;
	size_t			elem_index;

	if (argc < 4)
	{
		printf("Please give at least 3 arguments\n");
		return (1);
	}
	if (allocate_tab(&tab, ENV_SIZE, sizeof (char *)))
		exit_error(MSG, 1);
	index = 0;
	while (index < (size_t)argc)
	{
		if (add_tab(&tab, *(argv + index)))
			exit_error(MSG, 1);
		index ++;
	}
	printf("The tab is now full\n");
	tab_iter(&tab, print_string);
	printf("This was the tab\n");
	index = 0;
	while (index < (size_t)argc)
	{
		elem_index = get_elem_index(&tab, *(argv + index), ft_strcmp);
		if (elem_index != index)
			printf("Elem : %s is misplaced. Expected %ld and got %ld\n", *(argv + index), index, elem_index);
		else
			printf("Everything in place with elem %s at index %ld\n", *(argv + index), index);
		index ++;
	}
	free_gc();
	return (0);
}
