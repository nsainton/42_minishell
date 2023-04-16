/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:10:01 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/16 19:31:50 by nsainton         ###   ########.fr       */
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
