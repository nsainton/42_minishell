/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/14 11:52:36 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_names(const char **var_address, const char *identifier)
{
	size_t		i;
	const char	*env_var;

	i = 0;
	env_var = *var_address;
	while (*(env_var + i) && *(env_var + i) != '=')
		i ++;
	return (ft_strncmp(env_var, identifier, i - 1));
}

static void	del_string_tab(void *str)
{
	free_node(*(char **)str);
}

static char *get_env_var(struct s_tab *env, const char *identifier)
{
	char	**env_vars;
	size_t	i;

	if (! identifier)
		return (NULL);
	i = 0;
	env_vars = env->zones;
	while (i < env->len)
	{
		if (! compare_names(env_vars + i, identifier))
			return (*(env_vars + i));
		i ++;
	}
	return (NULL);
}

static char	*get_var_value(struct s_tab *env, const char *identifier)
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
static int	valid_identifier(const char *var)
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

static int	set_var(struct s_tab *env_list, const char *var)
{
	size_t	index;

	index = get_elem_index(env_list, var, compare_names);
	if (index >= tab->len)
		return (add_tab(env_list, &var));
	replace_tab_elem(env_list, &var, index, del_string_tab);
	return (0);
}

static int	set_var_value(struct s_tab *env_list, \
const char *identifier, const char *value)
{
	char	*var;
	size_t	index;
	size_t	varlen;

	var = gccalloc(ft_strlen(identifier) + ft_strlen(value) + 1);
	if (! var)
		return (ALLOCATION_ERROR);
	varlen = ft_strcat(var, identifier);
	varlen += ft_strcat(var + varlen, "=");
	ft_strcat(var + varlen, value);
	return (set_var(env_list, var));
}

/*
	We allocate shlvl / 10 + 2 here to have the right number of digits
	and keep a room for the null terminator.
*/
static int	set_shlvl(struct s_tab *env_list)
{
	char	*tmp;
	char	*newlvl;
	int		shlvl;
	size_t	len;

	tmp = get_var_value(env_list, "SHLVL");
	if (! tmp)
	{
		tmp = gc_strdup("SHLVL=1");
		return ((! tmp && add_tab(env_list, &tmp) * ALLOCATION_ERROR));
	}
	shlvl=ft_atoi(tmp);
	if (shlvl < 0)
		shlvl = 0;
	newlvl = gc_calloc(ft_strlen("SHLVL=") + shlvl / 10 + 2);
	if (! newlvl)
		return (ALLOCATION_ERROR);
	len = ft_strcat(newlvl, "SHLVL=");
	put_nb_tab(shlvl, newlvl + len, DEC);
	return (set_var(env_list, newlvl));
}

/*
	We allocate PATH_MAX + 5 and give cwd + 4 to getcwd
	to keep room for the "PWD=" declaration we need at the
	beginning of the env variable
*/
static int	set_pwd(struct s_tab *env_list)
{
	char	cwd[PATH_MAX + 5];
	char	*pwd;

	if (! getcwd(cwd + 4, PATH_MAX + 1))
		return (1);
	ft_memcpy(cwd, "PWD=", ft_strlen("PWD="));
	pwd = gc_strdup(cwd);
	if (! pwd)
		return (1);
	return (set_var(env_list, pwd));
}

static int	default_vars(struct s_tab *env_list)
{
	char	*tmp;

	if (set_shlvl(env_list))
		return (1);
	tmp = get_var_value(env_list, "PWD");
	if (! tmp && set_pwd(env_list))
		return (1);
	tmp = get_var_value(env_list, "_");
	if (! tmp && set_var_value("_", "/usr/bin/env"))
		return (1);
	return (0);
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

	env_variables = (char **)env->zones;
	i = 0;
	while (i < env->len)
	{
		ft_putendl_fd(*(env_variables + i), STDOUT_FILENO);
		i ++;
	}
}

/*
	if (cmd->args[0])
	{
		ft_dprintf(2, "env : minishell doesn't support arguments or options\n");
		d->errnum = 127;
	}
	else
		print_list_prefix(d->env->list_env, NULL);
	return (SUCCESS);
}
*/

/*
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
*/

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

/*
void	delete_env_line(t_list *start, t_list *to_del)
{
	while (start->next != to_del)
		start = start->next;
	start->next = to_del->next;
	to_del->content = 0;
}
*/
