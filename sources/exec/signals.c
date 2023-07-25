/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:10:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/25 18:01:03 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sigs(void)
{
	signal(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
}
/* 
void	init_sig(void f(int, siginfo_t*, void*), int sigid)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof sig);
	sig.sa_sigaction = f;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask,  sigid);
	sigaction(sigid, &sig, NULL);

} */


void	interrupt(int sig)
{
	(void)sig;

	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_child(int signal)
{
	exit_free_gc(128 + signal);
}