/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 14:27:55 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"

//Functions from file : gc_structure.c
t_gc	*getgc(void);

int		gc_realloc(void);

//Functions from file : strs.c
char	*gc_strdup(t_cchar *s);

char	*gc_strtrim(t_cchar *s1, t_cchar *set);

char	*gc_strjoin(t_cchar *s1, t_cchar *s2);

//Functions from file : split.c
char	**gc_split(t_cchar *s, char c);

//Functions from file : gc_del.c
int		free_gc(t_cint errcode);

int		free_nodes(t_csizet number, t_cint errcode);

int		free_node(void *node, t_cint errcode);

void	remove_nodes(size_t number);

//Functions from file : gc_management.c
int		gc_add(void *ptr);

int		gc_replace(void *old_ptr, void *new_ptr);

int		gc_add_array(void **array);

//Functions from file : gc_array.c
int		free_array_strings_size(char **array, t_csizet size, \
t_cint errcode);

int		free_array_strings_null(char **array, t_cint errcode);

//Functions from file : gc_alloc.c
void	*gcmalloc(size_t size);

void	*gccalloc(size_t nmemb, size_t size);

void	*gcrealloc(void *pointer, size_t old_size, size_t new_size);

//Functions from file : gc_helpers.c
size_t	gc_len(void);

void	print_collector(void);

#endif
