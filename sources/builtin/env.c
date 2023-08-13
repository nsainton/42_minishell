/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/13 16:25:10 by nsainton         ###   ########.fr       */
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
		if (! valid_env_var(*(envp + i)))
		{
			i ++;
			continue ;
		}
		env_node = gc_strdup(*(envp + i));
		if (! env_node || add_tab(env, env_node))
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
	if (allocate_tab(tmp->env_list, BASE_ENV_SIZE, sizeof (char *)))
		return (ALLOCATION_ERROR);
	return (allocate_tab(tmp->export_list, BASE_ENV_SIZE, sizeof (char *)));
}

struct s_env	*create_env(const char **envp)
{
	struct s_env	*env;

	if (allocate_room(&env))
		exit_free_gc(ALLOCATION_ERROR);
	if (envp && fill_env(env->env_list, envp))
		exit_free_gc(ALLOCATION_ERROR);
	if (default_vars(env->env_list))
		exit_free_gc(ALLOCATION_ERROR);
	if (export_list(env->env_list, env->export_list))
		exit_free_gc(ALLOCATION_ERROR);
	/*
	{
		my_env->list_env = basic_env();
		add_env_var("PWD=", my_env);
		add_env_var("OLDPWD=.", my_env);
		set_new_pwd(my_env);
	}
	else
	{
		my_env->is_empty = 0;
		my_env->list_env = copy_env(envp);
	}
	*/
	return (my_env);
}

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

int	print_env(t_data *d, t_command *cmd)
{
	d->errnum = 0;
	/* if (d->env->is_empty)
		return (SUCCESS); */
	if (cmd->args[0])
	{
		ft_dprintf(2, "env : minishell doesn't support arguments or options\n");
		d->errnum = 127;
	}
	else
		print_list_prefix(d->env->list_env, NULL);
	return (SUCCESS);
}

t_list 	*create_false_env(void)
{
	t_list	*my_env;
	char	*line;

	line = "SHLVL=1";
	my_env = gc_lstnew((void *) line);
	if (!my_env)
		exit_free_gc(ALLOCATION_ERROR);
	return (my_env);
}

/*
int	unset_env(t_data *d, t_command *cmd)
{
	int		i;
	t_list	*tmp;
	char	*line;

	d->errnum = 0;
	if (d->env->is_empty)
	{
		ft_dprintf(2, "env : unset : No such file or directory\n");
		return (127);
	}
	if (!cmd->args[0])
		return (SUCCESS);
	i = 0;
	tmp = d->env->list_env;
	while (cmd->args[i])
	{
		while (d->env->list_env)
		{
			line = (char *)d->env->list_env->content;
			if (!ft_strncmp(cmd->args[i], line, ft_strlen(cmd->args[i]))
				&& line[ft_strlen(cmd->args[i])] == '=')
				delete_env_line(tmp, d->env->list_env);
			d->env->list_env = d->env->list_env->next;
		}
		i++;
	}
	d->env->list_env = tmp;
	return (SUCCESS);
}
*/

void	delete_env_line(t_list *start, t_list *to_del)
{
	while (start->next != to_del)
		start = start->next;
	start->next = to_del->next;
	to_del->content = 0;
}
