/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:53:10 by nsainton          #+#    #+#             */
/*   Updated: 2023/01/12 20:40:53 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

noreturn void	error_exit(char *error)
{
	ft_printf("%s%s%s\n", RED, error, CRESET);
	exit(EXIT_FAILURE);
}
