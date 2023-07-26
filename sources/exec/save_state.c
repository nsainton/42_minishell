/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:03:07 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/26 15:05:05 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_state(const int action)
{
	static int	state;

	if (action > 0)
		state ++;
	else if (action == 0)
		state = 0;
	return (state);
}
