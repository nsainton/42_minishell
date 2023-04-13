/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:17:28 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/13 17:19:58 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	gc_len()
{
	t_gc	*collector;

	collector = getgc();
	if (! collector)
		return (0);
	return (collector->len);
}
