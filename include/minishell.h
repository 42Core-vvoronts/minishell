/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 13:29:34 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/elibft/include/elibft.h"
# include "../lib/elibft/include/elibft.h"

# include <ctype.h>
# include <signal.h>
# include <fcntl.h>
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
# define STACK_SIZE 256

typedef enum e_type
{
	AND,
	OR,
	GROUP,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	FILENAME,
	CONTENT,
	ARGUMENT,
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
	NOT_VALID_IDENTIFIER,
	NON_NUMERIC_EXIT,
	TOO_MANY_ARG_EXIT,
	TOO_MANY_ARG_CD,
	ERRNO_CD,
	OLDPWD_NOT_SET_CD,
	HOME_NOT_SET_CD,
	// Parser
	SYNTAX_ERROR,
	TOKEN_ERROR,
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

char *get_pathname(t_node *node);
void	error(void *data, t_datatype datatype, int error, bool terminate);
pid_t	efork(t_node *node);
void	eexecve(char *pathname, t_node *node);
char	*get_cmdname(void *node);
void	set_exitcode(void *node, int code);
int		eopen(char *pathname, int flags, int mode, t_node *node);
void	edup2(int oldfd, int newfd, t_node *node);

char	**get_var(t_ctx *ctx, char *varname);
char	*get_val(t_ctx *ctx, char *varname);
void	add_var(t_node *node, char *str);
int		init_ctx(t_ctx **ctx, char **envp);

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

void	process_argument(t_node *node);
void	process_content(t_node *node);

void	evaluate(t_node *node);
int		prompt(int argc, char **argv, char **envp);

// -- PARSING --
t_node	*parse(char *statement, t_ctx *ctx);

// -- LEXER --
t_tok	*lexer(char *statement);
void	handle_quotes(char **statement, t_tok **tokens);
void	handle_words(char **statement, t_tok **tokens);
void	handle_operators(char **statement, t_tok **tokens);
void	skip_spaces(char **statement);

t_type	typify(char *lexeme);
void	add_token(t_tok *new, t_tok **head, t_tok **current);

bool	is_open_parenthesis(char *lexeme);
bool	is_close_parenthesis(char *lexeme);
bool	is_pipe_symbol(char *lexeme);
bool	is_less(char *lexeme);
bool	is_greater(char *lexeme);
bool	is_and(char *lexeme);
bool	is_single_quote(char *lexeme);
bool	is_double_quote(char *lexeme);
bool	is_double_greater(char *lexeme);
bool	is_double_less(char *lexeme);

// -- SYNTAXER --
t_node	*syntaxer(t_tok *tok, t_ctx *ctx);
t_node	*group_or_expression(t_tok **tok, t_ctx *ctx);
t_node	*create_tree(t_tok **tok, int precedence, t_ctx *ctx);
int		get_precedence(t_type type);

t_node	*parse_list(t_tok **tok, t_ctx *ctx);
t_node	*parse_pipeline(t_tok **tok, t_ctx *ctx);
t_node	*parse_expression(t_tok **tok, t_ctx *ctx);
t_node	*parse_group(t_tok **tok, t_ctx *ctx);
t_node	*parse_redir(t_tok **tok, t_ctx *ctx);

bool	is_group_close(t_tok *tok);
bool	is_group_open(t_tok *tok);
bool	is_andor(t_tok *tok);
bool	is_pipe(t_tok *tok);
bool	is_redir(t_tok *tok);
bool	is_word(t_tok *tok);


void	step_forward(t_tok **tok);
//init
t_node	*init_node(t_type type, char *lexeme, t_node *left, t_node *right, t_ctx *ctx);
t_tok	*init_token(char *start, int len);


// errors
void	*error_exit(char *msg);
// -- PRINTER --
void print_tokens(t_tok *tokens);
void print_node(t_node *ast, int depth);
void save_tree(t_node *node);

#endif
