/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:51:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/08/16 09:06:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	choose_builtin(const char *str)
{
	if (! str)
		return (NULL);
	if (! ft_strcmp(str, "export"))
		return (export);
	if (! ft_strcmp(str, "echo"))
		return (echo);
	if (! ft_strcmp(str, "unset"))
		return (unset);
	if (! ft_strcmp(str, "cd"))
		return (cd);
	if (! ft_strcmp(str, "env"))
		return (env);
	if (! ft_strcmp(str, "pwd"))
		return (pwd);
	if (! ft_strcmp(str, "exit"))
		return (exit);
	return (NULL);
}
