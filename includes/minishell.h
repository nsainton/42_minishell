/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/03 13:22:03 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_int.h"

//Functions from file : pwd.c
char	*get_env_var(t_env *my_env, char *var);

int		print_pwd(t_command *cmd);

int		update_env_line(t_env *my_env, char *name, char *new_line);

t_list	*get_env_line(t_env *my_env, char *var);

//Functions from file : export.c
int		export_env(t_env *my_env, t_command *cmd);

int		is_valid_export(char *arg);

int		is_valid_name(char *arg);

int		modify_env(t_env *my_env, char *export);

//Functions from file : utils.c
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

//Functions from file : cd.c
int		cd(t_command *cmd, t_env *my_env);

int		set_new_pwd(t_env *my_env);

int		go_home(t_env *my_env, int set_old);

//Functions from file : builtin.c
int		which_builtin(t_command *cmd, t_env *my_env);

//Functions from file : pipex.c
void	sub_dup2(int read_fd, int write_fd);

void	close_used_pipes(t_data *d, t_command *cmd);

void	exec_command(t_data *d, t_command *cmd);

char	**make_command(t_command	*cmd);

int		go_pipe(t_data *d);

int		exec_pipeline(t_data	*d);

//Functions from file : check_path.c
int		check_path(t_command *cmd, t_env *my_env);

int		ft_arrlen(void **arr);

//Functions from file : files.c
void	get_infile(t_command *c);

void	get_outfile(t_command *c);

void	here_doc(char **limiters, int nb);

//Functions from file : signals.c
void	init_sigs(void);

void	init_sig(void f(int, siginfo_t*, void*), int sigid);

void	interrupt(int sig, siginfo_t *info, void *ucontext);

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