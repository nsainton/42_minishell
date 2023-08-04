/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:48:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/04 09:14:34 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
