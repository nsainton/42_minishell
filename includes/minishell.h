/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/15 18:53:14 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"

//Functions from file : gc_helpers.c
size_t	gc_len(void);

void	print_collector(void);

//Functions from file : gc_alloc.c
void	*gcmalloc(size_t size);

void	*gccalloc(size_t nmemb, size_t size);

void	*gcrealloc(void *pointer, size_t old_size, size_t new_size);

//Functions from file : gc_del.c
int		free_gc(t_cint errcode);

int		free_nodes(t_csizet number, t_cint errcode);

int		free_node(void *node, t_cint errcode);

//Functions from file : gc_structure.c
t_gc	*getgc(void);

int		gc_add(void *ptr);

int		gc_replace(void *old_ptr, void *new_ptr);

#endif
