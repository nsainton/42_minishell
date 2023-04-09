/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_receiving.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:45:45 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/15 00:27:45 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	update_message(int sig)
{
	static t_str	msg;
	int				signal;

	if (sig < 1)
	{
		tstr_init(&msg);
		return (update_byte(NULL, 0));
	}
	else if (! msg.size)
	{
		tstr_initstr(&msg, NULL, MSG_SIZE);
		if (! msg.size)
			error_exit("I really think that your computer is full");
	}
	else if (msg.len >= msg.size - 1)
	{
		msg.str = ft_realloc(msg.str, msg.size, 2 * msg.size);
		if (! msg.size)
			error_exit("I really think that your computer is full");
		msg.size = 2 * msg.size;
	}
	signal = update_byte(&msg, sig);
	if (signal == DONE)
		print_message(&msg);
	return (signal);
}

int	update_byte(t_str *message, int sig)
{
	static t_byte	bit;
	static t_byte	byte;

	if (sig < 1 || sig == DONE)
	{
		bit = 0;
		byte = 0;
		return (0);
	}
	if (! bit)
		byte = 0;
	if (sig == ON)
		byte |= 1 << bit;
	else if (sig == OFF)
		byte &= (-1 ^ 1 << bit);
	bit += 1;
	if (bit == 8)
	{
		if (! byte)
			return (DONE);
		*(message->str + message->len) = byte;
		message->len += 1;
		bit = 0;
	}
	return (CONTINUE);
}

int	check_client(pid_t	client)
{
	static pid_t	current;

	if (client == getpid() || (current && client && client != current))
		return (1);
	if (! (current && client))
		current = client;
	return (0);
}
