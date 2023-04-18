/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:48:28 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/18 13:54:26 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_env *my_env)
{
	char	*line;

	while (my_env->list_env)
	{
		line = (char *) my_env->list_env->content;
		if (!ft_strncmp("PWD", line, 3) && line[3] == '=')
			return (line);
		my_env->list_env = my_env->list_env->next;
	}
	return (NULL);
}

int	print_pwd(char **args)
{
	char	*line;

	if (args[0])
	{
		printf("pwd : too many arguments\n");
		return (1);
	}
	line = getcwd(NULL, 0);
	if (!line)
	{
		printf("%s\n", strerror(errno));
		return (errno);
	}
	printf("%s\n", &line[4]);
	free(line);
	return (SUCCESS);
}
