/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/03/31 16:08:14 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGC_H
# define LIBGC_H
# include "libgc_int.h"

//Functions from file : allocation.c
int		allocate_tab(t_tab *tab, size_t size, t_csizet elemsize);

int		realloc_tab(t_tab *tab, t_csizet newsize);

//Functions from file : management.c
int		add_tab(t_tab *tab, void *elem);

void	delelem_tab(t_tab *tab, void (*del)(void *));

void	del_tab(t_tab *tab);

//Functions from file : split.c
char	**gc_split(t_cchar *s, char c);

//Functions from file : itoa.c
char	*gc_itoa(int n);

//Functions from file : strs.c
char	*gc_strdup(t_cchar *s);

char	*gc_strtrim(t_cchar *s1, t_cchar *set);

char	*gc_strjoin(t_cchar *s1, t_cchar *s2);

char	*gc_substr(t_cchar *s, t_uint start, size_t len);

//Functions from file : gc_del.c
void	free_gc(void);

void	free_from(void *node);

void	free_nodes(t_csizet number);

void	free_node(void *node);

void	remove_nodes(size_t number);

//Functions from file : gc_management.c
int		gc_add(void *ptr);

int		gc_replace(void *old_ptr, void *new_ptr);

int		gc_add_array(void **array);

//Functions from file : gc_alloc.c
void	*gcmalloc(size_t size);

void	*gccalloc(size_t nmemb, size_t size);

void	*gcrealloc(void *pointer, size_t old_size, size_t new_size);

//Functions from file : lst_add.c
t_list	*gc_lstnew(void *content);

t_list	*gc_lstnew_cpy(t_cvoid *content, size_t size);

//Functions from file : lst_free.c
void	gc_lstdelone(t_list *lst, void (*del) (void *));

void	gc_lstclear(t_list **lst, void (*del) (void *));

void	gc_lstdel_front(t_list **lst, void (*del) (void *));

//Functions from file : gc_structure.c
t_gc	*getgc(void);

int		gc_realloc(void);

//Functions from file : gc_helpers.c
size_t	gc_len(void);

void	print_collector(void);

size_t	get_index(void *node);

void	*wrap_pointer(void *ptr);

//Functions from file : t_str.c
int		t_str_add(t_str *str, t_cchar c);

int		t_str_add_str(t_str *str, t_cchar *toadd);

int		t_str_alloc(t_str *str, t_csizet size);

int		t_str_realloc(t_str *str);

//Functions from file : gc_array.c
void	free_array_size(void **array, t_csizet size);

void	free_array_null(void **array);

#endif