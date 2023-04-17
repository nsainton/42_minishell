/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/04/17 15:53:31 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_int.h"
//Functions from file : export.c
int		export_env(t_env *my_env, char **args);

int		is_valid_export(char *arg);

int		is_valid_name(char *arg);

//Functions from file : utils.c
int		ft_error(int errno, char *msg);

void	print_list_prefix(t_list *lst, char *prefix);

t_list	*ft_lstnew_gc(void *content);

//Functions from file : env.c
t_env	*get_my_env(char **envp);

t_list	*copy_env(char **envp);

int		print_env(t_env *my_env, char **args);

int		unset_env(t_env *my_env, char **args);

//Functions from file : builtin.c
int		which_builtin(char *cmd, char **args, t_env *my_env);

//Functions from file : gc_del.c
int		free_gc(t_cint errcode);

int		free_nodes(t_csizet number, t_cint errcode);

//Functions from file : gc_alloc.c
void	*gcmalloc(size_t size);

void	*gccalloc(size_t nmemb, size_t size);

//Functions from file : gc_structure.c
t_gc	*getgc(void);

int		gc_add(void *ptr);

//Functions from file : gc_helpers.c
size_t	gc_len(void);

void	print_collector(void);

#endif