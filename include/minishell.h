/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 03:18:11 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/elibft/include/elibft.h"

# include <ctype.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <string.h>    // strlen
# include <stdlib.h>    // exit
# include <unistd.h>    // syscalls
# include <readline/readline.h>
# include <readline/history.h>

# define REDIR_FAIL 1

typedef enum e_type
{
	AND,
	OR,
	GROUP,
	PIPE,
	WORD_ZERO_QUOTES,
	WORD_SINGLE_QUOTES,
	WORD_DOUBLE_QUOTES,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_type;

// # define	GENERIC -1
// # define	MALLOC
// # define	OPEN_FAIL
// # define	EXECVE_FAIL
// # define	FORK_FAIL
// # define	PIPECALL
// # define	NOT_EXECUTABLE 126
// # define	CMD_NOT_FOUND 127
// # define	FILE_NOT_FOUND 1
// # define	PERMISSION_DENIED 1
// # define	INPUT 1
// # define	HEREDOC_INPUT 1
// # define	SYNTAX_ERROR 2
// # define	BUILTIN_MISUSE 2

typedef enum e_error
{
	GENERIC,
	MALLOC_FAIL,
	OPEN_FAIL,
	EXECVE_FAIL,
	FORK_FAIL,
	PIPE_FAIL,
	DUP_FAIL,
	NOT_EXECUTABLE,
	NOT_READABLE,
	NOT_WRITABLE,
	AMBIGUOUS_REDIR,
	CMD_NOT_FOUND,
	FILE_NOT_FOUND,
	PERMISSION_DENIED,
	BUILTIN_MISUSE,
	SYNTAX_ERROR,
	NOT_VALID_IDENTIFIER,
	NON_NUMERIC_EXIT,
	TOO_MANY_ARG_EXIT,
} t_error;

typedef enum e_datatype
{
	NONE,
	STRUCT_CTX,
	STRUCT_NODE,
}	t_datatype;

typedef struct s_ctx
{
	char	**envp;
	char	*ttyname;
	char	**stash;
	int		*fds;
	char	*hint;
	pid_t	exitcode;
	struct s_node	*head;
} t_ctx;

typedef struct s_node
{
	t_ctx			*ctx;
	t_type			type;
	char			*token;
	struct s_node	*left;
	struct s_node	*right;
} t_node;

typedef struct s_pipe
{
	int read;
	int write;
} t_pipe;

typedef struct s_tok
{
	t_type			type;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;

void	error(void *data, t_datatype datatype, int error, bool terminate);
pid_t	efork(t_node *node);
void	eexecve(char *pathname, t_node *node);
char	*get_cmdname(void *node);
void	set_exitcode(void *node, int code);
int		eopen(char *pathname, int flags, int mode, t_node *node);
void	edup2(int oldfd, int newfd, t_node *node);

char	**get_var(t_ctx *ctx, char *varname);
char	*get_val(t_ctx *ctx, char *varname);

void	process_and(t_node	*node);
void	process_or(t_node	*node);

int		allclean(t_node *node);

void	add_arg(char *arg, t_node *node);
char	*pop_arg(t_node *node);
void	prepare_argv(t_node *node);

void 	run_cmd(t_node *node);
char	*get_pathname(t_node *node);

int		get_exitcode(pid_t pid);
bool	is_exist(char *pathname);
bool	is_executable(char *pathname);
bool	is_pathname(char *cmd);
bool	is_ambiguous(char *pathname);
bool	is_readable(char *pathname);
bool	is_writable(char *pathname);

void	process_group(t_node *node);

void	run_echo(t_node *node);
void	run_cd(t_node *node);
void	run_pwd(t_node *node);
void	run_export(t_node *node);
void	run_unset(t_node *node);
void	run_env(t_node *node);
void	run_exit(t_node *node);

void	process_pipe(t_node *node);
int		open_pipe(t_pipe *p, t_node *node);
int		close_pipe(t_pipe *p);

void	process_redir_append(t_node *node);
void	process_redir_heredoc(t_node *node);
void	process_redir_in(t_node *node);
void	process_redir_out(t_node *node);

void	process_word_zero_quotes(t_node *node);
void	process_word_single_quotes(t_node *node);
void	process_word_double_quotes(t_node *node);

void	evaluate_node(t_node *node);

#endif
