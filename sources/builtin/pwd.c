/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:48:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/16 08:43:35 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	*get_env_var(const struct s_env *my_env, char *var)
{
	char	*line;
	int		len;
	t_list	*tmp;

	if (!var)
		return (NULL);
	tmp = my_env->list_env;
	len = ft_strlen(var);
	while (tmp && tmp->content)
	{
		line = (char *) tmp->content;
		tmp = tmp->next;
		if (! line)
			continue ;
		if (!ft_strncmp(var, line, len) && line[len] == '=')
			return (&line[len + 1]);
	}
	return (NULL);
}
*/

static int	valid_arg(const char *argument)
{
	if (*argument != '-' || ! *(argument + 1))
		return (1);
	if (*(argument + 1) == '-' && ! *(argument + 2))
		return (1);
	return (0);
}

static int	print_pwd(void)
{
	char	current[PATH_MAX + 1];

	if (! getcwd(current, PATH_MAX + 1))
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		return (1);
	}
	ft_putendl_fd(current, STDOUT_FILENO);
	return (0);
}

int	pwd(const char **arguments, struct s_env *env)
{
	(void)env;
	while (*arguments)
	{
		if (**arguments != '-')
			break ;
		if (! valid_arg(*arguments))
		{
			ft_dprintf(STDERR_FILENO, \
			"minishell: pwd: %s: invalid option\npwd: usage: pwd\n", \
			*arguments);
			return (SYNTAX_ERROR);
		}
		arguments ++;
	}
	return (print_pwd());
}
/*
int	print_pwd(t_command *cmd)
{
	char	*line;

	if (cmd->args[0] && is_option(cmd->args[0]))
	{
		ft_dprintf(2, "pwd : no options allowed \n");
		return (2);
	}
	line = getcwd(NULL, 0);
	if (!line)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (errno);
	}
	ft_printf("%s\n", line);
	free(line);
	return (SUCCESS);
}

int	update_env_line(t_env *my_env, char *name, char *new_line)
{
	t_list	*old;
	char	*new;

	old = get_env_line(my_env, name);
	new = gc_strjoin(name, "=");
	if (old && new)
	{
		old->content = gc_strjoin(new, new_line);
		if (!old->content)
			return (errno);
		return (0);
	}
	return (errno);
}

t_list	*get_env_line(t_env *my_env, char *var)
{
	char	*line;
	int		len;
	t_list	*tmp;

	if (!var)
		return (NULL);
	tmp = my_env->list_env;
	len = ft_strlen(var);
	while (tmp)
	{
		line = (char *) tmp->content;
		if (!ft_strncmp(var, line, len) && line[len] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
*/

/*
int	is_option(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i] == '-')
		i++;
	if (i != 0)
		return (1);
	else	
		return (0);
}
*/
