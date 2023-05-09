/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:41:43 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/09 10:25:23 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_var(t_cchar *line, size_t index, size_t length)
{
	char	*var_name;
	char	*var;

	var_name = gc_substr(line, index, length);
	if (! var_name)
		return (NULL);
	var = getenv(var_name);
	free_node(var_name);
	return (var);
}

static int	add_var_tstr(t_str *str, char *var, int parser)
{
	int	error;
	int	sp;

	error = 0;
	sp = 1;
	while (*var)
	{
		if (*var == ' ' && sp && ! parser)
		{
			error = t_str_add(str, ' ');
			sp = 0;
		}
		else
			error = t_str_add(str, crypt_char(*var));
		if (error)
			return (error);
		var ++;
	}
	return (NO_ERROR);
}
			
int	copy_env_variable(t_str *str, size_t *index, t_cchar *line, int parser)
{
	size_t	base_index;
	char	current;
	char	*var;
	int		error;

	base_index = *index;
	current = *(line + *index);
	while (current && (ft_isalnum(current) || current == '_'))
	{
		(*index)++;
		current = *(line + *index);
	}
	var = expand_env_var(line, base_index, *index - base_index);
	if (! var)
		return (NO_ERROR);
	error = t_str_add(str, BEG_VAR);
	error = (error || add_var_tstr(str, var, parser)) * error;
	return ((error || t_str_add(str, END_VAR)) * error);
}
