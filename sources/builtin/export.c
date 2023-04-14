/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:14:46 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/14 16:07:42 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env(t_env *my_env, char *arg)
{
	is_valid_export(arg);
	my_env = NULL;
}

int	is_valid_export(char *arg)
{


	if (ft_strchr(arg, '=') == NULL)
	{
		strerror(errno);
		return (2);
	}
	return (0);

}
