/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:10:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/27 13:21:23 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)signum;
	(void)info;
	(void)ucontext;
	//ft_printf("This is the line buffer : %s\n", rl_line_buffer);
	//is_child = save_state(-1);
	//ft_printf("I am the %s\n", is_child?"child":"parent");
	g_termsig = 128 + signum;
	keep_exit_status(g_termsig);
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	interrupt_child(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)info;
	(void)ucontext;

	g_termsig = 128 + signum;
	ft_putstr_fd("\n", 1);
	keep_exit_status(g_termsig);
	//rl_on_new_line();
	//ft_printf("Bonjour\n");
	//exit_free_gc(128 + signal);
}

void quit_child(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
		keep_exit_status(131);
	}
}

void	init_sigs(void)
{
	init_sig(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	reinit_sigs(void)
{
	//ft_printf("Reinitializing Signals\n");
	init_sig(SIGINT, interrupt_child);
	//signal(SIGQUIT, SIG_DFL);
}
