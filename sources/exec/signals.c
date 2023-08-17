/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:03:00 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/17 11:53:13 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static void	init_sig(int signum, void handler(int, siginfo_t*, void*))
{
	struct sigaction	action;

	ft_bzero(&action, sizeof action);
	action.sa_sigaction = handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, signum);
	sigaction(signum, &action, NULL);
}

static void	interrupt(int signum, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	g_termsig = 128 + signum;
	if (! rl_done)
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

/*
static void	interrupt_child(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)info;
	(void)ucontext;

	g_termsig = 128 + signum;
	keep_exit_status(g_termsig);
	ft_putstr_fd("\n", 1);
}
*/

/*
void quit_child(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
		keep_exit_status(131);
	}
}
*/

void	init_sigs(void)
{
	init_sig(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
}

/*
void	reinit_sigs(void)
{
	init_sig(SIGINT, interrupt_child);
}
*/
