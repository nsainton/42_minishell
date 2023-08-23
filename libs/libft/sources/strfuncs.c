/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:59:33 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/31 11:53:18 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	index;

	index = 0;
	while (*(src + index))
	{
		*(dest + index) = *(src + index);
		index ++;
	}
	*(dest + index) = 0;
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n && *(src + index))
	{
		*(dest + index) = *(src + index);
		index ++;
	}
	while (index < n)
	{
		*(dest + index) = 0;
		index ++;
	}
	return (dest);
}

size_t	ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dest);
	i = 0;
	while (i < n && *(src + i))
	{
		*(dest + dst_len + i) = *(src + i);
		i ++;
	}
	*(dest + dst_len + i) = 0;
	return (i);
}

size_t	ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (*(src + i))
	{
		*(dest + dest_len + i) = *(src + i);
		i ++;
	}
	*(dest + dest_len + i) = 0;
	return (dest_len + i);
}
