/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:41:43 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/15 09:55:15 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_var(const char *line, size_t index, \
size_t length, const struct s_tab *env)
{
	char	*var_name;
	char	*var;

	var_name = gc_substr(line, index, length);
	if (! var_name)
		return (NULL);
	var = get_env_var(env, var_name);
	free_node(var_name);
	return (var);
}

/*
static char	*format_var(t_cchar *var, int parser)
{
	char	*nvar;
	size_t	len;
	size_t	index;
	size_t	nindex;

	len = ft_strlen(var);
	nvar = gccalloc(len  + 1, sizeof *nvar);
	if (! nvar)
		return (NULL);
	index = 0;
	nindex = 0;
	while (*(var + index));
	{
		if (parser == D_QUOTES)
			*(nvar + nindex) = crypt_char(*(var + index));
		else
			*(nvar + nindex) = *(var + index);
		index ++;
		nindex ++;
	}
	return (nvar);
}
*/

static int	add_var_tstr(struct s_str *str, char *var, int parser)
{
	int	error;

	error = 0;
	while (*var)
	{
		if (! parser && (*var == ' '))
			error = t_str_add(str, *var);
		else
			error = t_str_add(str, crypt_char(*var));
		if (error)
			return (error);
		var ++;
	}
	return (NO_ERROR);
}

int	copy_env_variable(t_str *str, t_cstr *line, int parser, t_env *env)
{
	size_t	base_index;
	char	current;
	char	*var;
	int		error;

	base_index = line->index;
	current = *(line->str + line->index);
	while (current && (ft_isalnum(current) || current == '_'))
	{
		line->index ++;
		current = *(line->str + line->index);
	}
	var = expand_env_var(line->str, base_index, line->index \
	- base_index, env);
	if (! var)
		return (NO_ERROR);
	error = t_str_add(str, BEG_VAR);
	error = (error || add_var_tstr(str, var, parser)) * error;
	return ((error || t_str_add(str, END_VAR)) * error);
}
