/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 16:10:18 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"

//Functions from file : cd.c
int		cd(t_command *cmd, t_env *my_env);

int		set_new_pwd(t_env *my_env);

int		go_home(t_env *my_env, int set_old);

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

//Functions from file : echo.c
int		print_echo(t_command *cmd);

//Functions from file : builtin.c
int		which_builtin(t_command *cmd, t_env *my_env);

//Functions from file : utils.c
int		ft_error(int errno, char *msg);

void	print_list_prefix(t_list *lst, char *prefix);

t_list	*ft_lstnew_gc(void *content);

//Functions from file : env.c
t_env	*get_my_env(char **envp);

t_list	*copy_env(char **envp);

int		print_env(t_env *my_env, t_command *cmd);

int		unset_env(t_env *my_env, t_command *cmd);

void	delete_env_line(t_list *start, t_list *to_del);

//Functions from file : quotes.c
//Functions from file : copy_line.c
char	*copy_line(t_cchar *line);

//Functions from file : translation.c
int		crypt_char(t_cint c);

int		decrypt_char(t_cint c);

//Functions from file : debug.c
//Functions from file : check_path.c
int		check_path(t_command *cmd, t_env *my_env);

//Functions from file : pipex.c
//Functions from file : signals.c
void	init_sigs(void);

void	init_sig(void f(int, siginfo_t*, void*), int sigid);

void	interrupt(int sig, siginfo_t *info, void *ucontext);

//Functions from file : metachar.c
//Functions from file : parser.c
#endif
