/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:53:43 by nsainton          #+#    #+#             */
/*   Updated: 2023/08/18 17:53:43 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_int.h"
//Functions from file : check_redirections.c
int					check_in_redir(t_cchar *line, t_csizet index);

int					check_o_redir(char *line, size_t *len, t_csizet index);

//Functions from file : get_vars.c
char				*expand_env_var(const char *line, size_t index, \
size_t length, const struct s_tab *env);

int					copy_env_variable(t_str *str, t_cstr *line, int parser, \
const struct s_tab *env);

//Functions from file : invalid_redir.c
int					invalid_redir(t_cchar *line, t_csizet index, \
t_cchar current);

//Functions from file : quotes.c
//Functions from file : translation.c
int					crypt_char(t_cint c);

int					decrypt_char(t_cint c);

void				decrypt_string(char *s);

int					ft_ispunct(const int c);

//Functions from file : split_line.c
int					split_line(const char *line, \
struct s_ncommand **command, const struct s_tab *env);

//Functions from file : redirections.c
int					redirections(t_tab *redirs, t_str *line);

int					redirs_to_heredocs(t_tab *redirs, t_tab *heredocs);

//Functions from file : errors_messages.c
void				syntax_error(char token);

void				syntax_errors(char *token);

//Functions from file : fill_command.c
int					fill_commands(t_tab *command, char *line);

//Functions from file : debug.c
void				print_redir(t_redirection *redir, size_t no);

void				print_redirs(t_redirection *redirs);

void				print_args(char **args);

void				print_heredoc(t_heredoc *heredoc, size_t no);

void				print_heredocs(t_heredoc *heredoc);

void				print_command(t_ncommand *command, size_t no);

void				print_commands(t_ncommand *commands);

//Functions from file : valid_line.c
int					redirect_without_spaces(char *line, size_t *len);

int					invalid_operator(char *line, size_t *len);

//Functions from file : get_raw_line.c
int					get_raw_line(t_cchar *line, t_str *newline, \
const struct s_tab *env);

//Functions from file : finders.c
size_t				find_next(t_cchar *line, size_t index, t_cchar *tofind);

size_t				find_prev(t_cchar *line, size_t index, t_cchar *tofind);

int					find_mode(t_cchar *line, t_csizet index);

//Functions from file : clean_line.c
void				convert_var(signed char *line, size_t *len, t_csizet beg);

void				remove_var_symbols(signed char *line, size_t *len);

//Functions from file : debug.c
void				print_bin(void *elem, t_csizet elemsize);

void				print_tab_bin(t_tab *tab);

//Functions from file : connection.c
//Functions from file : pipex_utils.c
//Functions from file : signals.c
char				*choose_sig(int signum);

void				init_sigs(void);

//Functions from file : heredoc.c
int					heredocs(const struct s_ncommand *commands, \
const size_t commands_nb, const struct s_tab *env);

//Functions from file : heredocs_fds_list.c
//Functions from file : read_heredoc_line.c
int					write_line(const char *line, int write_fd, \
const struct s_tab *env);

//Functions from file : list_management.c
int					*getlist(const size_t size, const size_t elemsize);

//Functions from file : get_heredoc.c
int					get_heredoc(struct s_heredoc_infos *hd, \
struct s_heredoc *heredoc, const struct s_tab *env);

//Functions from file : execute_command.c
int					execute_commands(struct s_ncommand *commands, \
struct s_env *env);

//Functions from file : pre_execution.c
int					cleanup_before_exec(struct s_ncommand *commands, \
const size_t index, const size_t commands_nb);

int					pre_execution(struct s_redir *redirs, \
struct s_heredoc *heredocs);

//Functions from file : find_in_path.c
char				*find_in_path(const char *path, const char *command);

//Functions from file : get_path.c
int					getpath(char *command, char **command_path, \
struct s_tab *env);

//Functions from file : execute_one_command.c
int					handle_exit_status(const int wstatus);

int					execute_command(struct s_ncommand *command, \
struct s_env *env);

//Functions from file : make_redirections.c
int					make_redirections(struct s_redir *redirections, \
struct s_heredoc *heredocs);

//Functions from file : exit_free.c
void				exit_message(const int status, const char *message);

_Noreturn void		exit_free_gc(const int status);

int					keep_exit_status(const int exit_status);

//Functions from file : redirs.c
//Functions from file : dups.c
//Functions from file : fdlist_management.c
struct s_list		**get_fdlist(void);

struct s_list		*ft_list_find(struct s_list *begin_list, \
const void *data_ref, int (*cmp)());

void				del_node(struct s_list **lst, struct s_list *node, \
void (*del)(void *));

void				clear_fdlist(void);

//Functions from file : fds_list.c
int					s_open(const char *pathname, int flags, mode_t mode);

int					isdifferent_pointer(const int *a, const int *b);

int					s_close(int fd);

int					s_dup2(int oldfd, int newfd);

int					s_pipe(int pipefd[2]);

//Functions from file : fdlist_init.c
int					fdlist_init(void);

//Functions from file : files.c
//Functions from file : save_stds.c
int					save_stds(const int to_open);

//Functions from file : exec_cmds.c
//Functions from file : exec_one.c
//Functions from file : make_pipes.c
int					make_pipes(struct s_ncommand *commands);

//Functions from file : check_path.c
//Functions from file : tab_wrappers.c
void				del_tab_elem(struct s_tab *tab, const void *elem, \
int (*cmp)(), void (*del)(void *));

void				replace_tab_elem(struct s_tab *tab, void *elem, \
const size_t index, void (*del)(void *));

size_t				get_elem_index(struct s_tab *tab, const void *elem, \
int (*cmp)());

int					copy_tab(struct s_tab *newtab, \
const struct s_tab *oldtab);

int					insertion_sort_tab(struct s_tab *tab, int (*cmp)());

//Functions from file : debug.c
void				print_fd(void *fd);

void				print_fdlist(void);

//Functions from file : dup_list.c
//Functions from file : hash_map_init.c
struct s_hashmap	*getmap(size_t (*hash_function)(const void *), \
void (*del)(void *));

//Functions from file : hash_map_find.c
struct s_list		*hash_map_find(const struct s_hashmap *map, \
const void *elem, int (*cmp)());

//Functions from file : hash_map_management.c
struct s_list		**get_hash_list(const struct s_hashmap *map, \
const void *elem);

void				hash_map_delete(struct s_hashmap *map, \
struct s_list *elem);

void				hash_map_clear(struct s_hashmap *map);

int					hash_map_add(struct s_hashmap *map, void *elem);

//Functions from file : echo.c
int					echo(const char **args, struct s_env *env);

//Functions from file : exit.c
int					exit_builtin(const char **args, struct s_env *env);

//Functions from file : export_env.c
//Functions from file : unset_env.c
//Functions from file : pwd.c
int					pwd(const char **arguments, struct s_env *env);

//Functions from file : unset.c
int					unset(const char **args, struct s_env *env);

//Functions from file : cd.c
int					cd(const char **args, struct s_env *env);

//Functions from file : env.c
int					compare_names(const char **var_address, \
const char *identifier);

void				del_string_tab(void *str);

char				*get_var_value(const struct s_tab *env, \
const char *identifier);

int					valid_identifier(const char *var);

int					set_var(struct s_tab *env_list, const char *var);

int					set_var_value(struct s_tab *env_list, \
const char *identifier, const char *value);

struct s_env		*create_env(const char **envp);

void				print_env(struct s_tab *env);

int					env(const char **args, struct s_env *environnement);

int					print_exportlist(struct s_tab *export);

//Functions from file : export.c
int					export(const char **args, struct s_env *env);

//Functions from file : builtin.c
t_builtin			choose_builtin(const char *str);

//Functions from file : minishell.c
//Functions from file : commands_exec.c
int					commands_exec(const char *line, struct s_env *env);

//Functions from file : ft_list_remove_if.c
void				ft_list_remove_if(t_list **begin_list, void *data_ref, \
int (*cmp)(), void (*free_fct)(void *));

//Functions from file : copy_list.c
struct s_list		*copy_list(struct s_list *lst);

//Functions from file : sort_list.c
void				ft_list_sort(t_list **begin_list, int (*cmp)());

//Functions from file : parser.c
//Functions from file : metachar.c
#endif