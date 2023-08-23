/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_until.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:54:11 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/22 16:44:59 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_until(t_cchar *s, t_cchar *base, int *err, t_csizet nb)
{
	char	*cpy;
	int		result;

	cpy = malloc(nb + 1);
	if (! cpy)
	{
		*err = 2;
		return (0);
	}
	ft_strlcpy(cpy, s, nb + 1);
	result = atoi_errors(cpy, base, err);
	free(cpy);
	return (result);
}
