/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_messages.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:43:50 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/18 11:42:24 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	We set a default value for SIGSTKFLT because it is not defined on all
	architectures and we use it for initialization.
*/
#ifndef SIGNAL_MESSAGES_H
# define SIGNAL_MESSAGES_H
# ifndef SIGSTKFLT
#  define SIGSTKFLT 0
# endif
# define SIGHUP_MESSAGE "Hangup"
# define SIGQUIT_MESSAGE "Quit"
# define SIGINT_MESSAGE "\n"
# define SIGILL_MESSAGE "Illegal instruction"
# define SIGTRAP_MESSAGE "Trace/breakpoint trap"
# define SIGABRT_MESSAGE "Aborted"
# define SIGBUS_MESSAGE "Bus error"
# define SIGFPE_MESSAGE "Floating point exception"
# define SIGKILL_MESSAGE "Killed"
# define SIGUSR1_MESSAGE "User defined signal 1"
# define SIGUSR2_MESSAGE "User defined signal 2"
# define SIGSEGV_MESSAGE "Segmentation fault"
# define SIGALRM_MESSAGE "Alarm clock"
# define SIGSTKFLT_MESSAGE "Stack fault"
# define SIGXCPU_MESSAGE "CPU time limit exceeded"
# define SIGXFSZ_MESSAGE "File size limit exceeded"
# define SIGVTALRM_MESSAGE "Virtual timer expired"
# define SIGPROF_MESSAGE "Profiling timer expired"
# define SIGPOLL_MESSAGE "Power failure"
# define SIGSYS_MESSAGE "Bad system call"
# define SIGPIPE_MESSAGE ""
# define DFL_MESSAGE ""
#endif
