/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 03:00:25 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/13 01:21:22 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_message(t_str *msg)
{
	if (msg->str)
		write(1, msg->str, msg->len);
	tstr_init(msg);
}
