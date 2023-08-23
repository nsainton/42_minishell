/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tstr_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:47:28 by nsainton          #+#    #+#             */
/*   Updated: 2023/07/28 09:26:31 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	tstr_reinit(t_str *str)
{
	if (str->str != NULL)
		free(str->str);
	ft_bzero(str, sizeof * str);
}

int	tstr_init(t_str *str, size_t size)
{
	if (! size)
		return (EXIT_FAILURE);
	ft_bzero(str, sizeof * str);
	str->str = ft_calloc(size, sizeof * str->str);
	if (! str->str)
		return (EXIT_FAILURE);
	str->size = size;
	return (EXIT_SUCCESS);
}

int	tstr_initstr(t_str *tstr, char *str, size_t buffsize)
{
	size_t	len;
	size_t	size;

	if (str == NULL)
		str = "";
	len = ft_strlen(str);
	size = len + 1;
	if (size < buffsize)
		size = buffsize;
	tstr->str = ft_calloc(size, sizeof *(tstr->str));
	if (tstr->str == NULL)
		return (EXIT_FAILURE);
	ft_strlcpy(tstr->str, str, size);
	tstr->len = len;
	tstr->size = size;
	return (EXIT_SUCCESS);
}

int	tstr_cpy(t_str *dst, const t_str *src)
{
	if (dst->size > 0)
		free(dst->str);
	dst->str = ft_calloc(src->size, 1);
	if (dst->str == NULL)
		return (EXIT_FAILURE);
	ft_strlcpy(dst->str, src->str, src->size);
	dst->size = src->size;
	dst->len = src->len;
	return (EXIT_SUCCESS);
}
