/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/13 11:55:54 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"

//Functions from file : gc_del.c
int		free_gc(t_cint errcode);

int		free_nodes(t_csizet number, t_cint errcode);

//Functions from file : gc_alloc.c
void	*gcmalloc(size_t size);

//Functions from file : gc_structure.c
t_gc	*getgc(void);

int		gc_add(void *ptr);

#endif
