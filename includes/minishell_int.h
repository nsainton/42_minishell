/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:33:27 by avedrenn          #+#    #+#             */
/*   Updated: 2023/05/10 14:23:15 by avedrenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//includes
#ifndef MINISHELL_INT_H
# define MINISHELL_INT_H
// Preprocessor includes
# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
//Compile the executable with libreadline (-lreadline)
//End of Prepocessor includes

// Preprocessor defines
# define TRASH_SIZE 50
# define ENTER "Entering function : %s\n"
# define LEAVE "Leaving function : %s\n"
# define EPRINT ft_dprintf(STDERR_FILENO, ENTER, __func__);
# define LPRINT ft_dprintf(STDERR_FILENO, LEAVE, __func__);
# define SUCCESS 0
// ENUM Declarations

/*
METACHARACTERS : Any metacharacter except ;
PIPE : Designates a | or a \n
EXIT_STATUS : For the variable $?
*/
enum e_types
{
	METACHARACTERS = 1 << 0,
	PIPE = 1 << 1,
	OUTPUT_REDIRECTION = 1 << 2,
	INPUT_REDIRECTION = 1 << 3,
	DOUBLE_INPUT_REDIR = 1 << 4,
	APPEND_REDIRECTION = 1 << 5,
	ENV_VARIABLE = 1 << 6,
	EXIT_STATUS = 1 << 7,
};

enum e_minierrors
{
	NO_ERROR = 0,
	ALLOCATION_ERROR = 20,
	NO_COLLECTOR,
	OVERFLOW,
	NOT_IN_COLLECTOR,
	ADD_ERROR
};
// End of ENUM Declarations

enum e_states
{
	NO_STATE,
	S_QUOTES,
	D_QUOTES
};

//Structures declarations

struct s_arg
{
	char			*argument;
	enum e_types	type;
};

struct	s_command
{
	char	*command;
	char	*path;
	char	**options;
	char	**args;
	t_uint	last;
	char	*in;
	char	*out;
	int		is_here_doc;
	char	**limiters;
	int		fd_in;
	int		fd_out;
	int		err;
};

struct	s_gc
{
	void	**memzones;
	size_t	len;
	size_t	size;
};

struct s_env
{
	t_list	*list_env;
	char	*path;
	int		is_empty;
};

struct	s_data
{
	struct s_command	**cmds;
	int					cmds_nb;
	struct s_env		*env;
	int					here_doc;
	char				**limiters;
	int					*pipes;
	int					pipes_nb;
	int					index;
	int					pid;
	int					errnum;
};

//End of structures declarations

//Type definitions
typedef enum e_types		t_types;

typedef enum e_minierrors	t_minierrors;

typedef struct s_command	t_command;

typedef struct s_arg		t_arg;

typedef struct s_gc			t_gc;

typedef struct s_env		t_env;

typedef struct s_data		t_data;

//End of type definitions

#endif
