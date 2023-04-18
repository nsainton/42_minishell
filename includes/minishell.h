/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/18 18:19:10 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"

//Functions from file : pwd.c
char	*get_pwd(t_env *my_env);

int		print_pwd(t_env *my_env, char **args);

//Functions from file : export.c
int		export_env(t_env *my_env, char **args);

int		is_valid_export(char *arg);

int		is_valid_name(char *arg);

//Functions from file : builtin.c
int		which_builtin(char *cmd, char **args, t_env *my_env);

//Functions from file : utils.c
int		ft_error(int errno, char *msg);

void	print_list_prefix(t_list *lst, char *prefix);

t_list	*ft_lstnew_gc(void *content);

//Functions from file : env.c
t_env	*get_my_env(char **envp);

t_list	*copy_env(char **envp);

int		print_env(t_env *my_env, char **args);

int		unset_env(t_env *my_env, char **args);

void	delete_env_line(t_list *start, t_list *to_del);

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
void	free_gc(void);

void	free_nodes(t_csizet number);

void	free_node(void *node);

void	remove_nodes(size_t number);

//Functions from file : gc_management.c
int		gc_add(void *ptr);

int		gc_replace(void *old_ptr, void *new_ptr);

int		gc_add_array(void **array);

//Functions from file : gc_array.c
void	free_array_size(void **array, t_csizet size);

void	free_array_null(void **array);

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

//Functions from file : gc_helpers.c
size_t	gc_len(void);

void	print_collector(void);

//Functions from file : parser.c
int		init_parser(t_parser *parser);

int		add_parser(t_parser *parser, const t_metachar mc);

int		add_parser_char(t_parser *parser, t_cchar c, t_cchar state);

#endif
