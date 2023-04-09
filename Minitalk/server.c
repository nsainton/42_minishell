/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:25:37 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/15 05:25:33 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_global = -1;

static void	srv_start(void)
{
	int	pid;

	pid = (int)getpid();
	ft_printf("%s      #######                                        \
	\n\
    /       ###                                                       \n\
   /         ##                                                       \n\
   ##        #                      ##                                \n\
    ###                             ##                                \n\
   ## ###           /##  ###  /###   ##    ###      /##  ###  /###    \n\
    ### ###        / ###  ###/ #### / ##    ###    / ###  ###/ #### / \n\
      ### ###     /   ###  ##   ###/  ##     ###  /   ###  ##   ###/  \n\
        ### /##  ##    ### ##         ##      ## ##    ### ##         \n\
          #/ /## ########  ##         ##      ## ########  ##         \n\
           #/ ## #######   ##         ##      ## #######   ##         \n\
            # /  ##        ##         ##      ## ##        ##         \n\
  /##        /   ####    / ##         ##      /  ####    / ##         \n\
 /  ########/     ######/  ###         ######/    ######/  ###        \n\
/     #####        #####    ###         #####      #####    ###       \n\
|                                                                     \n\
                                                                      %s\n", \
	GRN, CRESET);
	ft_printf("%sListening at : %s%d%s\n", BLU, GRN, pid, CRESET);
}

static void	signal_status(int *signal)
{
	g_global = -1;
	update_message(0);
	check_client(0);
	if (! *signal)
	{
		print_color("\nWhat happened bro, what did you want to say ?\n", \
		's', RED, 1);
		print_color("Try again if you want bro\n", 's', GRN, 1);
	}
	else
		*signal = RECEIVED;
}

static void	handle_server(int sig, siginfo_t *sigi, void *context)
{
	int		signal;
	int		checked;

	(void)context;
	g_global ^= g_global;
	checked = check_client(sigi->si_pid);
	if (getpid() == sigi->si_pid)
		signal = 0;
	else if (! checked)
		signal = update_message(sig);
	if (checked && getpid() != sigi->si_pid)
	{
		check_client(0);
		print_color("\nTalk to your bro bro\n", 's', RED, 1);
		sleep(1);
		return ;
	}
	if (! signal || signal == DONE)
		signal_status(&signal);
	if (! checked)
		kill(sigi->si_pid, signal);
}

int	main(void)
{
	t_sigaction	action;

	init_sigaction(&action, handle_server);
	srv_start();
	while (1)
	{
		if (g_global == -1)
		{
			g_global = 1;
			pause();
		}
		else
		{
			g_global = 1;
			sleep(1);
		}
		if (g_global == 1)
			kill(getpid(), ERROR);
	}
	return (0);
}
