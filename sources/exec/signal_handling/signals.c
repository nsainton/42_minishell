/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:03:00 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/21 12:10:44 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include "signal_messages.h"

static void	init_sigarray(char **sigarray)
{
	*(sigarray + SIGHUP) = SIGHUP_MESSAGE;
	*(sigarray + SIGQUIT) = SIGQUIT_MESSAGE;
	//*(sigarray + SIGINT) = SIGINT_MESSAGE;
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

/*
	If you don't use the SA_RESTART flag for your
	sigaction, the wait call for your child when
	running execve to execute another file will
	fail and return without waiting for said child.
	Thus you won't be able to wait for it and it
	will basically create a zombie.
*/
static void	init_sig(int signum, void handler(int, siginfo_t*, void*))
{
	struct sigaction	action;

	ft_bzero(&action, sizeof action);
	action.sa_sigaction = handler;
	action.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, signum);
	sigaction(signum, &action, NULL);
}

/*
	If you stuff a '\n' into readline buffer without telling it that
	we moved onto a new line, it will add another newline character and
	thus you will see two newlines after you hit ^C
*/
static void	interrupt(int signum, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	g_termsig = 128 + signum;
	if (! rl_done)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	//rl_done = 1;
}

void	init_sigs(void)
{
	init_sig(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
