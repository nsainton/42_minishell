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

//Functions from file : minishell.c
void						init(char **av, char **envp, t_data *data);

//Functions from file : metachar.c
//Functions from file : parser.c
//Functions from file : save_stds.c
int							save_stds(const int mode);

//Functions from file : dups.c
void						dup_in_out(int fd_in, int fd_out);

void						dup_pipe(t_data *d);

void						dupnclose(int fd1, int fd2);

//Functions from file : get_heredoc.c
int							getheredoc(struct s_heredoc_infos *hd, \
struct s_heredoc *heredoc);

//Functions from file : heredoc.c
int							heredoc(t_command *command);

//Functions from file : check_path.c
int							check_path(t_command *cmd, t_env *my_env);

int							is_a_directory(char *path);

int							ft_arrlen(void **arr);

//Functions from file : files.c
int							get_infile(t_command *c, t_redir *r);

int							get_outfile(t_command *c, t_redir *r, \
const int mode);

//Functions from file : signals.c
void						init_sigs(void);

void						init_sig(void f(int, siginfo_t*, void*), \
int sigid);

void						interrupt(int sig, siginfo_t *info, \
void *ucontext);

//Functions from file : pipex_utils.c
void wait_for_childs(t_data	*d);

char						**make_command(t_command	*cmd);

void						close_used_pipes(t_data *d, t_command *cmd);

//Functions from file : redirs.c
int							make_redirs(t_data *d, t_command *cmd);

//Functions from file : exit_free.c
void						exit_free_gc(int status);

int							keep_exit_status(const int exit_status);

//Functions from file : exec_cmds.c
int							set_data(t_data *d);

int							exec_pipeline(t_data *d);

void						exec_command_in_pipeline(t_data *d);

//Functions from file : exec_one.c
int							exec_one(t_data *d);

int							exec_builtin_parent(t_data *d, \
t_command *cmd);

void						exec_w_execve(t_data *d, t_command *cmd);

//Functions from file : connection.c
t_command					**\
get_commands_reference(t_ncommand *original);

//Functions from file : debug.c
void						print_bin(void *elem, t_csizet elemsize);

void						print_tab_bin(t_tab *tab);

//Functions from file : commands_exec.c
void						commands_exec(t_cchar *line, t_data *data);

//Functions from file : translation.c
int							crypt_char(t_cint c);

int							decrypt_char(t_cint c);

void						decrypt_string(char *s);

//Functions from file : split_line.c
int							split_line(t_cchar *line, \
t_ncommand **command, t_env *env);

//Functions from file : debug.c
void						print_redir(t_redirection *redir, size_t no);

void						print_redirs(t_redirection *redirs);

void						print_args(char **args);

void						print_heredoc(t_heredoc *heredoc, size_t no);

void						print_heredocs(t_heredoc *heredoc);

void						print_command(t_ncommand *command, size_t no);

void						print_commands(t_ncommand *commands);

//Functions from file : redirections.c
int							redirections(t_tab *redirs, t_str *line);

int							redirs_to_heredocs(t_tab *redirs, \
t_tab *heredocs);

//Functions from file : valid_line.c
int							redirect_without_spaces(char *line, \
size_t *len);

int							invalid_operator(char *line, size_t *len);

//Functions from file : finders.c
size_t						find_next(t_cchar *line, size_t index, \
t_cchar *tofind);

size_t						find_prev(t_cchar *line, size_t index, \
t_cchar *tofind);

int							find_mode(t_cchar *line, t_csizet index);

//Functions from file : clean_line.c
void						convert_var(signed char *line, size_t *len, \
t_csizet beg);

void						remove_var_symbols(signed char *line, \
size_t *len);

//Functions from file : errors_messages.c
void						syntax_error(char token);

void						syntax_errors(char *token);

//Functions from file : invalid_redir.c
int							invalid_redir(t_cchar *line, t_csizet index, \
t_cchar current);

//Functions from file : get_raw_line.c
int							get_raw_line(t_cchar *line, t_str *newline, \
t_env *env);

//Functions from file : get_vars.c
int							copy_env_variable(t_str *str, t_cstr *line, \
int parser, t_env *env);

//Functions from file : quotes.c
//Functions from file : fill_command.c
int							fill_commands(t_tab *command, char *line);

//Functions from file : check_redirections.c
int							check_in_redir(t_cchar *line, \
t_csizet index);

int							check_o_redir(char *line, size_t *len, \
t_csizet index);

//Functions from file : test_parsing.c
//Functions from file : builtin.c
int							exec_builtin(t_command *cmd, t_data *d);

int							is_builtin(t_command *cmd, t_data *d);

//Functions from file : export.c
int							export_env(t_data *d, t_command *cmd);

int							is_valid_export(char *arg);

int							is_valid_name(char *arg);

int							modify_env(t_env *my_env, char *export);

//Functions from file : pwd.c
char						*get_env_var(t_env *my_env, char *var);

int							print_pwd(t_command *cmd);

int							update_env_line(t_env *my_env, char *name, \
char *new_line);

t_list						*get_env_line(t_env *my_env, char *var);

//Functions from file : utils.c
void						print_list_prefix(t_list *lst, char *prefix);

t_list						*ft_lstnew_gc(void *content);

char						**envlist_to_arr(t_list *env);

//Functions from file : exit.c
int							exit_builtin(char **args, int *errnum);

//Functions from file : cd.c
int							cd(t_command *cmd, t_data *d);

int							set_new_pwd(t_env *my_env);

int							go_home(t_env *my_env, int set_old);

//Functions from file : env.c
t_env						*get_my_env(char **envp);

t_list						*copy_env(char **envp);

int							print_env(t_data *d, t_command *cmd);

int							unset_env(t_data *d, t_command *cmd);

void						delete_env_line(t_list *start, \
t_list *to_del);

//Functions from file : echo.c
int							print_echo(t_data *d, t_command *cmd);

int							is_true_optn(char *str);

int							print_exit_status(t_data *d, \
t_command *cmd);

#endif