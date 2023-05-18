/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/15 11:55:15 by avedrenn         ###   ########.fr       */
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
int		export_env(t_data *d, t_command *cmd);

int		is_valid_export(char *arg);

int		is_valid_name(char *arg);

int		modify_env(t_env *my_env, char *export);

//Functions from file : echo.c
int		print_echo(t_command *cmd);

//Functions from file : builtin.c
int		which_builtin(t_command *cmd, t_env *my_env);

//Functions from file : utils.c
void	print_list_prefix(t_list *lst, char *prefix);

t_list	*ft_lstnew_gc(void *content);

char	**envlist_to_arr(t_list *env);

//Functions from file : echo.c
int		print_echo(t_data *d, t_command *cmd);

int		is_true_optn(char *str);

int		print_exit_status(t_data *d, t_command *cmd);

//Functions from file : env.c
t_env	*get_my_env(char **envp);

t_list	*copy_env(char **envp);

int		print_env(t_data *d, t_command *cmd);

int		unset_env(t_data *d, t_command *cmd);

void	delete_env_line(t_list *start, t_list *to_del);

//Functions from file : cd.c
int		cd(t_command *cmd, t_data *d);

int		set_new_pwd(t_env *my_env);

int		go_home(t_env *my_env, int set_old);

//Functions from file : builtin.c
int		which_builtin(t_command *cmd, t_data *d);

//Functions from file : pipex.c
void	sub_dup2(int read_fd, int write_fd);

void	close_used_pipes(t_data *d, t_command *cmd);

void	exec_command(t_data *d, t_command *cmd);

char	**make_command(t_command	*cmd);

int		go_pipe(t_data *d);

int		exec_pipeline(t_data	*d);

//Functions from file : pipex.c
void	sub_dup2(int read_fd, int write_fd);

//Functions from file : translation.c
int		crypt_char(t_cint c);

int		decrypt_char(t_cint c);

//Functions from file : get_vars.c
int		copy_env_variable(t_str *str, size_t *index, t_cchar *line, \
int parser);

//Functions from file : valid_line.c
int		redirect_without_spaces(char *line, size_t *len);

//Functions from file : debug.c
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

//Functions from file : metachar.c
//Functions from file : parser.c
#endif
