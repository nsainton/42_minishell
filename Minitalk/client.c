/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:40:44 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/15 05:25:49 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_global = 0;

void	handle_client(int sig, siginfo_t *sigi, void *context)
{
	int	signal;

	(void)context;
	if (getpid() == sigi->si_pid)
		error_exit("Wtf bro, you stopped listening ?");
	if (sig == RECEIVED)
	{
		ft_printf("The server listening at %s%d%s acknowledges the \
successful reception of the message", GRN, sigi->si_pid, CRESET);
		exit(EXIT_SUCCESS);
	}
	signal = send_message(NULL);
	g_global = 0;
	kill(sigi->si_pid, signal);
}

int	main(int ac, char **av)
{
	t_sigaction	action;
	pid_t		receiver;
	int			signal;

	init_sigaction(&action, handle_client);
	if (ac != 3)
		error_exit("Incorrect number of arguments");
	receiver = ft_atoi(*(av + 1));
	if (receiver < 1)
		error_exit("PID must be positive for Minitalk to talk");
	if (kill(receiver, 0))
		error_exit("Who you talking to?");
	signal = send_message(*(av + 2));
	kill(receiver, signal);
	while (1)
	{
		sleep(3);
		if (g_global)
			kill(getpid(), ERROR);
		g_global = 1;
	}
	return (0);
}
