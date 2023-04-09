/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librairies.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 01:04:17 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/14 23:12:05 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRAIRIES_H
# define LIBRAIRIES_H
# define ON SIGUSR1
# define OFF SIGUSR2
# define CONTINUE SIGUSR1
# define RECEIVED SIGUSR2
# define DONE 1000
# define ERROR SIGUSR1
# ifdef MSG_SIZE
#  undef MSG_SIZE
# endif
# define MSG_SIZE 100
# include "libft.h"
# include <signal.h>
# include <stdnoreturn.h>
#endif
