/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:33:27 by avedrenn          #+#    #+#             */
/*   Updated: 2023/04/12 11:00:50 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//includes
#ifndef MINISHELL_INT_H
# define MINISHELL_INT_H
# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
//Compile the executable with libreadline (-lreadline)

enum e_types
{
	METACHARACTERS = 1 << 0, //Any metacharacter except ;
	PIPE = 1 << 1, // | and newline
	OUTPUT_REDIRECTION = 1 << 2,
	INPUT_REDIRECTION = 1 << 3,
	DOUBLE_INPUT_REDIR = 1 << 4,
	APPEND_REDIRECTION = 1 << 5,
	ENV_VARIABLE = 1 << 6,
	EXIT_STATUS = 1 << 7, // $?
};

struct s_arg
{
	char			*argument;
	enum e_types	type;
};

struct	s_command
{
	char	*command;
	t_list	*options;
	t_list	*args;
	t_uint	last;
	t_uint	pipeline;
	int		in;
	int		out;
	int		err;
};

struct	s_gc
{
	void	**memzones;
	size_t	len;
	size_t	size;
};

typedef enum e_types		t_types;

typedef struct s_command	t_command;

typedef struct s_arg		t_arg;

typedef struct s_gc			t_gc;
/* struct	s_data
{
	t_list	*args;
	t_list	*infiles;
	t_list	*outfiles;
	t_list	*commands;
} */

#endif
