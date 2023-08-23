/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgc_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:07:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/22 16:16:52 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGC_INT_H
# define LIBGC_INT_H
# include "libft.h"
# include <stdlib.h>
# define TRASH_SIZE 50

enum e_collector_errors
{
	COLLECTOR_NO_ERROR,
	COLLECTOR_ALLOCATION_ERROR = 20,
	NO_COLLECTOR,
	COLLECTOR_OVERFLOW,
	NOT_IN_COLLECTOR,
	COLLECTOR_ADD_ERROR,
	COLLECTOR_UNKNOWN_ERROR
};

struct	s_gc
{
	void	**memzones;
	size_t	len;
	size_t	size;
};

struct	s_tab
{
	void	*tab;
	size_t	elemsize;
	size_t	len;
	size_t	size;
};

typedef struct s_gc		t_gc;

typedef struct s_tab	t_tab;
#endif
