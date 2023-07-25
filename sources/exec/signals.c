/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:10:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/07/25 17:12:43 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sigs(void)
{
	init_sig(interrupt, SIGINT);
	signal(SIGQUIT, SIG_IGN);
}

void	init_sig(void f(int, siginfo_t*, void*), int sigid)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof sig);
	sig.sa_sigaction = f;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask,  sigid);
	sigaction(sigid, &sig, NULL);

}


void	interrupt(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	(void)info;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
