/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:03:00 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/18 12:28:14 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include "signal_messages.h"

static void	init_sigarray(char **sigarray)
{
	*(sigarray + SIGHUP) = SIGHUP_MESSAGE;
	*(sigarray + SIGQUIT) = SIGQUIT_MESSAGE;
	*(sigarray + SIGINT) = SIGINT_MESSAGE;
	*(sigarray + SIGILL) = SIGILL_MESSAGE;
	*(sigarray + SIGTRAP) = SIGTRAP_MESSAGE;
	*(sigarray + SIGABRT) = SIGABRT_MESSAGE;
	*(sigarray + SIGBUS) = SIGBUS_MESSAGE;
	*(sigarray + SIGFPE) = SIGFPE_MESSAGE;
	*(sigarray + SIGKILL) = SIGKILL_MESSAGE;
	*(sigarray + SIGUSR1) = SIGUSR1_MESSAGE;
	*(sigarray + SIGUSR2) = SIGUSR2_MESSAGE;
	*(sigarray + SIGSEGV) = SIGSEGV_MESSAGE;
	*(sigarray + SIGALRM) = SIGALRM_MESSAGE;
	*(sigarray + SIGSTKFLT) = SIGSTKFLT_MESSAGE;
	*(sigarray + SIGXCPU) = SIGXCPU_MESSAGE;
	*(sigarray + SIGXFSZ) = SIGXFSZ_MESSAGE;
	*(sigarray + SIGVTALRM) = SIGVTALRM_MESSAGE;
	*(sigarray + SIGPROF) = SIGPROF_MESSAGE;
	*(sigarray + SIGPOLL) = SIGPOLL_MESSAGE;
	*(sigarray + SIGSYS) = SIGSYS_MESSAGE;
}

char	*choose_sig(int signum)
{
	int			i;
	static char	*signals[32];

	if (signum > 31)
		return (DFL_MESSAGE);
	if (*signals)
		return (*(signals + signum));
	i = 0;
	while (i < 32)
	{
		*(signals + i) = DFL_MESSAGE;
		i ++;
	}
	init_sigarray(signals);
	return (*(signals + signum));
}

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

void	init_sigs(void)
{
	init_sig(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
