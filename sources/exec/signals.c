/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:10:21 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/21 18:16:10 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sig(void)
{
	struct sigaction siga;

	ft_bzero(&siga, sizeof siga);
	siga.sa_sigaction = interrupt;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaddset(&siga.sa_mask, SIGINT);
	sigaction(SIGINT, &siga, NULL);
}

_Noreturn void	interrupt(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	(void)info;
	ft_printf("Thanks for using control-c\n");
	free_gc();
	exit(0);
}