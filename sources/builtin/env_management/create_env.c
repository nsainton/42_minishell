/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainto <nsainton@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:56:12 by nsainto           #+#    #+#             */
/*   Updated: 2023/08/23 11:03:43 by nsainto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
