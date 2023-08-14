/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:36:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/14 11:00:33 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#define MSG "No mo mem bruv, can't reMEMber. Hahaha\nSee ya bruv"

/*
	This test teaches to remember that when storing a char * element into a
	struct s_tab object, you have to give the char * by address (thus a
	char ** pointer). This also means that all the comparison functions and
	deletions function will have to take into account that they will receive
	a char **. Cast and dereference if needed
*/
static _Noreturn void exit_error(const char *message, int error)
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

static void	print_string(const char **s)
{
	printf("%s\n", *s);
}

static int	compare_strings(const char **s1, const char *s)
{
	return (ft_strcmp(*s1, s));
}

static void	del_string_tab(void *str)
{
	free_node(*(char **)str);
}

static char	*gc_strmapi(const char *str, int (*f)(int))
{
	char			*ns;
	unsigned int	i;

	ns = gccalloc(ft_strlen(str) + 1, sizeof * str);
	if (! ns)
		return (NULL);
	i = 0;
	while (*(str + i))
	{
		*(ns + i) = f(*(str + i));
		i ++;
	}
	return (ns);
}

static int	replace_string(struct s_tab *tab, size_t index)
{
	char	*ns;
	char	*s;

	s = *(char **)(tab->tab + index * tab->elemsize);
	ns = gc_strmapi(s, ft_toupper);
	if (! ns)
		return (1);
	replace_tab_elem(tab, &ns, index, del_string_tab);
	return (0);
}

int	main(int argc, char **argv)
{
	struct s_tab	tab;
	char			*tmp;
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
		tmp = gc_strdup(*(argv + index));
		printf("This is the temp variable : %s\n", tmp);
		if (! tmp || add_tab(&tab, &tmp))
			exit_error(MSG, 1);
		index ++;
	}
	printf("The tab is now full\n");
	tab_iter(&tab, print_string);
	printf("This was the tab\n");
	index = 0;
	while (index < (size_t)argc)
	{
		elem_index = get_elem_index(&tab, *(argv + index), compare_strings);
		if (elem_index != index)
			printf("Elem : %s is misplaced. Expected %ld and got %ld\n", *(argv + index), index, elem_index);
		else
			printf("Everything in place with elem %s at index %ld\n", *(argv + index), index);
		index ++;
	}
	index = 0;
	while (index < (size_t)argc)
	{
		if (replace_string(&tab, index))
			exit_error(MSG, 1);
		index ++;
	}
	printf("The tab has been replaced\n");
	tab_iter(&tab, print_string);
	printf("This was the tab\n");
	index = 0;
	while (index < (size_t)argc)
	{
		printf("-------Before deletion--------\n");
		tab_iter(&tab, print_string);
		del_tab_elem(&tab, *(argv + index), compare_strings, del_string_tab);
		printf("---------After deletion--------\n");
		tab_iter(&tab, print_string);
		printf("-------------------------------\n");
		index ++;
	}
	free_gc();
	return (0);
}
