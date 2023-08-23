/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:17:59 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/29 14:14:19 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr)
		ptr ++;
	return (ptr - s);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && *(s + i))
		i ++;
	return (i);
}

size_t	tablen(const void *tab, size_t elemsize)
{
	char		nullelem[300];
	const char	*ptr;
	size_t		index;

	if (elemsize > 300)
		return (SIZE_MAX);
	index = 0;
	ptr = (const char *)tab;
	ft_bzero(nullelem, sizeof nullelem);
	while (ft_memcmp(ptr + index, nullelem, elemsize))
		index += elemsize;
	return (index / elemsize);
}
