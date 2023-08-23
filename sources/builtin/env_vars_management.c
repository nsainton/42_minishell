/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainto <nsainton@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:42:43 by nsainto           #+#    #+#             */
/*   Updated: 2023/08/23 10:44:05 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(const struct s_tab *env, const char *identifier)
{
	char	**env_vars;
	size_t	i;

	if (! identifier)
		return (NULL);
	i = 0;
	env_vars = env->tab;
	while (i < env->len)
	{
		if (! compare_names((const char **)env_vars + i, identifier))
			return (*(env_vars + i));
		i ++;
	}
	return (NULL);
}

char	*get_var_value(const struct s_tab *env, const char *identifier)
{
	char	*var;

	var = get_env_var(env, identifier);
	if (! var)
		return (NULL);
	while (*var && *var != '=')
		var ++;
	return (var + (*var == '='));
}

/*
	Reminder : A valid name is a name beginning by an alphabetical character
	or an underscore and containing only alphanumerical characters or
	underscores.
	We check until the '=' sign if our variable is a valid identifier
*/
int	valid_identifier(const char *var)
{
	if (! ft_isalpha(*var) && *var != '_')
		return (0);
	var ++;
	while (*var && *var != '=')
	{
		if (! ft_isalnum(*var) && *var != '_')
			return (0);
		var ++;
	}
	return (1);
}

/*
	This function is meant to be used only by the export
	function directly and by set_var_value.
	The export function will need it to export a variable
	whose value is NULL
*/
int	set_var(struct s_tab *env_list, const char *var)
{
	size_t	index;

	index = get_elem_index(env_list, var, compare_names);
	if (index >= env_list->len)
		return (add_tab(env_list, &var));
	replace_tab_elem(env_list, &var, index, del_string_tab);
	return (0);
}

/*
	We allocate one more spot for the '=' sign
*/
int	set_var_value(struct s_tab *env_list, \
const char *identifier, const char *value)
{
	char	*var;
	size_t	varlen;

	var = gccalloc(ft_strlen(identifier) + ft_strlen(value) + 2, \
	sizeof * var);
	if (! var)
		return (ALLOCATION_ERROR);
	varlen = ft_strcat(var, identifier);
	varlen += ft_strcat(var + varlen, "=");
	ft_strcat(var + varlen, value);
	return (set_var(env_list, var));
}
