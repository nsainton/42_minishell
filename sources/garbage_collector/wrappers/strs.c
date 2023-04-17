/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:01 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 13:30:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strdup(t_cchar *s)
{
	char	*ns;

	ns = ft_strdup(s);
	if (! (ns && gc_add(ns)))
		return (ns);
	free(ns);
	return (NULL);
}

char	*gc_strtrim(t_cchar *s1, t_cchar *set)
{
	char	*ns;

	ns = ft_strtrim(s1, set);
	if (! (ns && gc_add(ns)))
		return (ns);
	free(ns);
	return (NULL);
}

char	*gc_strjoin(t_cchar *s1, t_cchar *s2)
{
	char	*ns;

	ns = ft_strjoin(s1, s2);
	if (! (ns && gc_add(ns)))
		return (ns);
	free(ns);
	return (NULL);
}
