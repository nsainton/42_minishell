/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainto <nsainton@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:58:25 by nsainto           #+#    #+#             */
/*   Updated: 2023/08/23 10:58:34 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_var(char *var, const char *exported_var)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*(exported_var + i) && *(exported_var + i) != '=')
		i ++;
	*var = 0;
	i += (*(exported_var + i) == '=');
	len = ft_strncat(var, exported_var, i);
	if (*(exported_var + i - 1) != '=')
		return ;
	len += ft_strcat(var + len, "\"");
	len += ft_strcat(var + len, exported_var + i);
	ft_strcat(var + len, "\"");
}

static int	compare_strings(const char **s1, const char **s2)
{
	return (ft_strcmp(*s1, *s2));
}

/*
	2 blocks more in the allocation to keep room for the
	two '"' if needed.
*/
int	print_exportlist(struct s_tab *export)
{
	char			**export_variables;
	struct s_tab	tab;
	size_t			i;
	char			*new_var;

	if (copy_tab(&tab, export) || \
	insertion_sort_tab(&tab, compare_strings))
		return (ALLOCATION_ERROR);
	export_variables = tab.tab;
	i = 0;
	while (i < export->len)
	{
		new_var = ft_calloc(ft_strlen(*(export_variables + i)) + 3, \
		sizeof **export_variables);
		if (! new_var)
			return (ALLOCATION_ERROR);
		fill_var(new_var, *(export_variables + i));
		ft_putendl_fd(new_var, STDOUT_FILENO);
		free(new_var);
		i ++;
	}
	free_node(tab.tab);
	return (0);
}
