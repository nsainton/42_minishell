/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainto <nsainton@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:02:13 by nsainto           #+#    #+#             */
/*   Updated: 2023/08/23 11:02:38 by nsainto          ###   ########.fr       */
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
