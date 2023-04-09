/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:54:27 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/15 01:07:00 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "structures.h"

//Functions from data_receiving.c [3 functions]

int				update_message(int sig);

int				update_byte(t_str *message, int sig);

int				check_client(pid_t client);

//Functions from data_sending.c [1 functions]

int				send_message(char *message);

//Functions from error.c [1 functions]

noreturn void	error_exit(char *error);

//Functions from init.c [0 functions]

void			init_sigaction(t_sigaction *action, t_action handler);

void			init_message(t_message *message);

//Functions from printing.c [0 functions]

void			print_message(t_str *msg);

#endif
