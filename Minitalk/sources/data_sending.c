/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_sending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:02:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/14 23:13:16 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_message(char *message)
{
	static char		*msg;
	static t_byte	bit;

	if (message)
		msg = message;
	if (*msg)
	{
		if (bit == 8)
		{
			bit = 0;
			msg ++;
		}
		if (*msg & 1 << bit ++)
			return (ON);
		else
			return (OFF);
	}
	return (OFF);
}
