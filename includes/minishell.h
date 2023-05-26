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

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"

//Functions from file : cd.c
int		cd(t_command *cmd, t_data *d);

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
int		print_echo(t_data *d, t_command *cmd);

int		is_true_optn(char *str);

int		print_exit_status(t_data *d, t_command *cmd);

//Functions from file : builtin.c
int		which_builtin(t_command *cmd, t_data *d);

//Functions from file : utils.c
void	print_list_prefix(t_list *lst, char *prefix);

t_list	*ft_lstnew_gc(void *content);

char	**envlist_to_arr(t_list *env);

//Functions from file : env.c
t_env	*get_my_env(char **envp);

t_list	*copy_env(char **envp);

int		print_env(t_data *d, t_command *cmd);

int		unset_env(t_data *d, t_command *cmd);

void	delete_env_line(t_list *start, t_list *to_del);

//Functions from file : gc_del.c
void	free_gc(void);

void	free_nodes(t_csizet number);

void	free_node(void *node);

void	remove_nodes(size_t number);

//Functions from file : test_parsing.c
int		test(void);

//Functions from file : quotes.c
//Functions from file : redirections.c
int		redirections(t_tab *redirs, t_str *line);

//Functions from file : get_raw_line.c
int		get_raw_line(t_cchar *line, t_str *newline);

//Functions from file : copy_line.c
char	*copy_line(t_cchar *line);

//Functions from file : clean_line.c
void	convert_var(signed char *line, size_t *len, t_csizet beg, \
char prev);

void	remove_var_symbols(signed char *line, size_t *len);

//Functions from file : translation.c
int		crypt_char(t_cint c);

int		decrypt_char(t_cint c);

void	decrypt_string(char *s);

//Functions from file : errors_messages.c
void	syntax_error(char token);

void	syntax_errors(char *token);

//Functions from file : check_redirections.c
int		check_in_redir(t_cchar *line, t_csizet index);

int		check_o_redir(char *line, size_t *len, t_csizet index);

//Functions from file : get_vars.c
int		copy_env_variable(t_str *str, size_t *index, t_cchar *line, \
int parser);

//Functions from file : valid_line.c
int		redirect_without_spaces(char *line, size_t *len);

int		invalid_operator(char *line, size_t *len);

//Functions from file : debug.c
//Functions from file : fill_command.c
//Functions from file : finders.c
size_t	find_next(t_cchar *line, size_t index, t_cchar *tofind);

size_t	find_prev(t_cchar *line, size_t index, t_cchar *tofind);

int		find_mode(t_cchar *line, t_csizet index);

//Functions from file : check_path.c
int		check_path(t_command *cmd, t_env *my_env);

int		ft_arrlen(void **arr);

//Functions from file : pipex.c
void	sub_dup2(int read_fd, int write_fd);

void	close_used_pipes(t_data *d, t_command *cmd);

void	exec_command(t_data *d, t_command *cmd);

char	**make_command(t_command	*cmd);

int		go_pipe(t_data *d);

int		exec_pipeline(t_data	*d);

//Functions from file : signals.c
void	init_sigs(void);

void	init_sig(void f(int, siginfo_t*, void*), int sigid);

void	interrupt(int sig, siginfo_t *info, void *ucontext);

//Functions from file : files.c
void	get_infile(t_command *c);

void	get_outfile(t_command *c);

void	here_doc(char **limiters, int nb);

//Functions from file : metachar.c
//Functions from file : parser.c
#endif