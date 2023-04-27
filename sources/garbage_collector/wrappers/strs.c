/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:01 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/25 14:35:43 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strdup(t_cchar *s)
{
	char	*ns;

	ns = ft_strdup(s);
	return (wrap_pointer(ns));
}

char	*gc_strtrim(t_cchar *s1, t_cchar *set)
{
	char	*ns;

	ns = ft_strtrim(s1, set);
	return (wrap_pointer(ns));
}

char	*gc_strjoin(t_cchar *s1, t_cchar *s2)
{
	char	*ns;

	ns = ft_strjoin(s1, s2);
	return (wrap_pointer(ns));
}

char	*gc_substr(t_cchar *s, t_uint start, size_t len)
{
	char	*ns;

	ns = ft_substr(s, start, len);
	return (wrap_pointer(ns));
}
