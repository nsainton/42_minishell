/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/25 17:56:32 by nsainton         ###   ########.fr       */
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

char	*gc_substr(t_cchar *s, t_uint start, size_t len);

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

//Functions from file : t_str.c
int		t_str_add(t_str *str, t_cchar c);

int		t_str_add_str(t_str *str, t_cchar *toadd);

int		t_str_alloc(t_str *str, t_csizet size);

//Functions from file : gc_helpers.c
size_t	gc_len(void);

void	print_collector(void);

void	*wrap_pointer(void *ptr);

//Functions from file : quotes.c
void	change_state(t_parser *parser, t_cchar meta);

int		parse_shell_line(t_cchar *line, t_parser *parser);

int		copy_right_chars(t_parser *parser);

t_list	*create_strings_array(t_parser *parser);

//Functions from file : copy_line.c
char	*copy_line(t_cchar *line);

//Functions from file : debug.c
void	print_line(t_metachar *mc, size_t size);

//Functions from file : metachar.c
t_uchar	set_mcstate(const t_parser *parser, const char c);

//Functions from file : parser.c
int		init_parser(t_parser *parser);

int		add_parser(t_parser *parser, const t_metachar mc);

char	*parser_to_string(t_parser *parser);

void	print_parser_infos(t_parser *parser);

void	print_parser(t_parser *parser);

#endif
