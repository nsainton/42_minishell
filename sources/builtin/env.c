/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:02:57 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/23 10:58:41 by nsainto          ###   ########.fr       */
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

