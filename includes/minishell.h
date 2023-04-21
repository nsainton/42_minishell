/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/21 18:20:08 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_int.h"

//Functions from file : pwd.c
char	*get_env_var(t_env *my_env, char *var);

int		print_pwd(t_command *cmd);

//Functions from file : export.c
int		export_env(t_env *my_env, t_command *cmd);

int		is_valid_export(char *arg);

int		is_valid_name(char *arg);

//Functions from file : utils.c
int		ft_error(int errno, char *msg);

void	print_list_prefix(t_list *lst, char *prefix);

t_list	*ft_lstnew_gc(void *content);

//Functions from file : echo.c
int		print_echo(t_command *cmd);

//Functions from file : env.c
t_env	*get_my_env(char **envp);

t_list	*copy_env(char **envp);

int		print_env(t_env *my_env, t_command *cmd);

int		unset_env(t_env *my_env, t_command *cmd);

void	delete_env_line(t_list *start, t_list *to_del);

//Functions from file : builtin.c
int		which_builtin(t_command *cmd, t_env *my_env);

//Functions from file : check_path.c
//Functions from file : signals.c
void	init_sig(void);
_Noreturn void	interrupt(int sig, siginfo_t *info, void *ucontext);

//Functions from file : split.c
char	**gc_split(t_cchar *s, char c);

//Functions from file : strs.c
char	*gc_strdup(t_cchar *s);

char	*gc_strtrim(t_cchar *s1, t_cchar *set);

char	*gc_strjoin(t_cchar *s1, t_cchar *s2);

//Functions from file : gc_del.c
void	free_gc();

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

//Functions from file : gc_array.c
void	free_array_size(void **array, t_csizet size);

void	free_array_null(void **array);

#endif