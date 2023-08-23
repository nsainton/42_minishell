/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/23 10:50:52 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strchrnul(const char *s, const int c)
{
	while (*s && *s != c)
		s ++;
	return ((char *)s);
}

/*
	Here, in the return, we check that identifier is the same length as the
	portion of the var before the '=' sign so that it doesn't return true for
	special cases like $HOME_A where it in facts returns $HOME because
	strncmp("HOME", "HOME_A", 4) returns 0.
	Added length_until_equal variable because of the two different ways
	I was using this function. Identifier is in fact a wrong name and can
	sometimes hold the value of a whole variable.
*/
int	compare_names(const char **var_address, const char *identifier)
{
	size_t		i;
	const char	*env_var;
	size_t		length_until_equal;

	i = 0;
	env_var = *var_address;
	length_until_equal = ft_strchrnul(identifier, '=') - identifier;
	while (*(env_var + i) && *(env_var + i) != '=')
		i ++;
	return (ft_strncmp(env_var, identifier, i) || \
	(i != length_until_equal));
}

void	del_string_tab(void *str)
{
	free_node(*(char **)str);
}


static int	fill_env(struct s_tab *env, const char **envp)
{
	char	*env_node;
	size_t	i;

	i = 0;
	while (*(envp + i))
	{
		if (! (valid_identifier(*(envp + i)) && \
		ft_strchr(*(envp + i), '=')))
		{
			i ++;
			continue ;
		}
		env_node = gc_strdup(*(envp + i));
		if (! env_node || add_tab(env, &env_node))
			return (ALLOCATION_ERROR);
		i ++;
	}
	return (0);
}

static int	allocate_room(struct s_env **env)
{
	struct s_env	*tmp;

	*env = gccalloc(1, sizeof **env);
	if (! *env)
		return (ALLOCATION_ERROR);
	tmp = *env;
	tmp->env_list = gccalloc(1, sizeof * tmp->env_list);
	if (! tmp->env_list)
		return (ALLOCATION_ERROR);
	tmp->export_list = gccalloc(1, sizeof * tmp->export_list);
	if (! tmp->export_list)
		return (ALLOCATION_ERROR);
	if (allocate_tab(tmp->env_list, ENV_SIZE, sizeof (char *)))
		return (ALLOCATION_ERROR);
	return (allocate_tab(tmp->export_list, ENV_SIZE, \
	sizeof (char *)));
}



static int	export_list(struct s_tab *env_list, struct s_tab *export_list)
{
	char	*var;
	size_t	i;

	i = 0;
	while (i < env_list->len)
	{
		var = gc_strdup(*(char **)(env_list->tab + i * env_list->elemsize));
		if (! var || add_tab(export_list, &var))
			return (1);
		i ++;
	}
	return (0);
}

struct s_env	*create_env(const char **envp)
{
	struct s_env	*env;

	if (allocate_room(&env))
		return (NULL);
	if (envp && fill_env(env->env_list, envp))
		return (NULL);
	if (default_vars(env->env_list))
		return (NULL);
	if (export_list(env->env_list, env->export_list))
		return (NULL);
	return (env);
}

/*
t_list	*copy_env(char **envp)
{
	int		i;
	t_list	*list_env;
	t_list	*new;

	list_env = gc_lstnew((void *) envp[0]);
	i = 1;
	while (envp[i])
	{
		new = gc_lstnew((void *) envp[i]);
		ft_lstadd_back(&list_env, new);
		i ++;
	}
	return (list_env);
}
*/

void	print_env(struct s_tab *env)
{
	char	**env_variables;
	size_t	i;

	env_variables = (char **)env->tab;
	i = 0;
	while (i < env->len)
	{
		ft_putendl_fd(*(env_variables + i), STDOUT_FILENO);
		i ++;
	}
}

int	env(const char **args, struct s_env *environnement)
{
	if (! (args && *args))
	{
		print_env(environnement->env_list);
		return (0);
	}
	if (**args == '-')
	{
		ft_dprintf(STDERR_FILENO, "env: unrecognized option '%s'\n\
Try 'reading minishell subject' for more information\n", *args);
		return (125);
	}
	ft_dprintf(STDERR_FILENO, "env: no argument allowed\nSorry bruv\n");
	return (125);
}

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
