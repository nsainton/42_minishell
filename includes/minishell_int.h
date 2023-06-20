/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:33:27 by avedrenn          #+#    #+#             */
/*   Updated: 2023/06/20 23:08:11 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//includes
#ifndef MINISHELL_INT_H
# define MINISHELL_INT_H
// Preprocessor includes
# include "libft.h"
# include "libgc.h"
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
# include <string.h>
# include <dirent.h>
//Compile the executable with libreadline (-lreadline)
//End of Prepocessor includes

// Preprocessor defines
# define PARSER_SIZE 50
# define REDIRS_SIZE 10
# define SERROR "minishell: syntax error near unexpected token `"
# define ENTER "Entering function : %s\n"
# define LEAVE "Leaving function : %s\n"
# define EPRINT ft_dprintf(STDERR_FILENO, ENTER, __func__);
# define LPRINT ft_dprintf(STDERR_FILENO, LEAVE, __func__);
# define SUCCESS 0
# define SPECIALS "'\"? <>|$"
# define REDIRS "<>|"
# define SEPARATORS " <>"
// End of Preprocessor defines

// ENUM Declarations
/*
METACHARACTERS : Any metacharacter except ;
PIPE : Designates a | or a \n
EXIT_STATUS : For the variable $?
*/
enum e_types
{
	METACHARACTERS = 1 << 0,
	PIPES = 1 << 1,
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
	SYNTAX_ERROR = 2,
	ALLOCATION_ERROR = 20,
	OVERFLOW,
	UNKNOWN_ERROR
};

/*
This enum controls the state of the parser while looking for the
"quoted state" of the charcters in the input line
*/
enum e_states
{
	NO_STATE,
	S_QUOTES,
	D_QUOTES
};

/*
This enum is used to define the replacement characters for the special ones
in the input string
*/
enum e_specials
{
	S_PACE = -10,
	DOLLAR,
	ES,
	O_RED,
	I_RED,
	PIPE,
	BEG_VAR,
	END_VAR,
};

//This enum informs me if the state of the parser has changed
enum e_changes
{
	UNCHANGED,
	CHANGED
};
// End of ENUM Declarations

//Structures declarations

struct s_arg
{
	char			*argument;
	enum e_types	type;
};

struct	s_heredoc
{
	int		fd;
	char	*limiter;
};

struct s_redir
{
	int		fd;
	char	mode;
	char	*file;
};

struct	s_command
{
	char				*command;
	char				*path;
	char				**args;
	t_uint				last;
	struct s_heredoc	**heredocs;
	struct s_redir		**redirs;
	int					fd_in;
	int					fd_out;
	int					err;
};


struct	s_ncommand
{
	char				*command;
	char				**args;
	struct s_heredoc	*heredocs;
	struct s_redir		*redirs;
};

struct s_pipeline
{
	t_list	*commands;
};

struct s_env
{
	t_list	*list_env;
	char	*path;
	int		is_empty;
};

/*
struct s_metachar
{
	char	c;
	t_uchar	state;
};

struct s_parser
{
	struct s_metachar	*meta;
	int					state;
	size_t				len;
	size_t				size;
}
*/

struct	s_data
{
	struct s_command	**cmds;
	int					cmds_nb;
	struct s_env		*env;
	int					p[2];
	int					prev_pipe;
	int					index;
	int					*pid;
	int					save_in;
	int					save_out;
	int					errnum;
};

//End of structures declarations

//Type definitions
typedef enum e_types		t_types;

typedef enum e_minierrors	t_minierrors;

typedef struct s_command	t_command;

typedef struct s_ncommand	t_ncommand;

typedef struct s_arg		t_arg;

typedef struct s_env		t_env;

typedef struct s_data		t_data;

typedef struct s_metachar	t_metachar;

typedef struct s_parser		t_parser;

typedef struct s_redir		t_redir;

typedef struct s_redir		t_redirection;

typedef struct s_heredoc	t_heredoc;

//End of type definitions

#endif
