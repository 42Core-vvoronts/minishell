/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 10:31:01 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/elibft/include/elibft.h"

# define _POSIX_C_SOURCE 200809L
# include <errno.h>
# include <ctype.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

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

typedef enum e_sigset
{
	IS_PROMPT,
	IS_BINARY,
	IS_RUNNING,
	IS_HEREDOC,
	IS_IGNORE
}	t_sigset;

# define SIGNO -1
# define FULL 1
# define CMD 0
# define PROGRAMM "minishell"
# define TOK 0xf000000000000000
# define FILE_NOT_FOUND "No such file or directory"
# define CMD_NOT_FOUND "command not found"
# define AMBIG_REDIR "ambiguous redirect"
# define NOT_VALID_IDN "not a valid identifier"
# define EXIT_NON_NUM "numeric argument required"
# define TOO_MANY_ARG "too many arguments"
# define CD_OLDPWD "OLDPWD not set"
# define CD_HOME "HOME not set"
# define IS_DIR "Is a directory"
# define SYNTAX_ERROR "syntax error near unexpected token"

# define EXIT "exit"
# define EXPORT "export"
# define CD "cd"

extern volatile sig_atomic_t	g_signal;;
typedef char					*t_m[5];
typedef struct s_ctx
{
	char			**envp;
	char			**export;
	char			**stash;
	int				fdin;
	int				fdout;
	int				exitcode;
	struct s_node	*head;
	struct s_tok	*headtok;
	bool			errlex;
	bool			errsyn;
} t_ctx;

typedef struct s_node
{
	t_ctx			*ctx;
	t_type			type;
	char			*token;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_tok
{
	t_type			type;
	char			*lexeme;
	struct s_tok	*next;
}	t_tok;

typedef struct s_pipe
{
	int	read;
	int	write;
}	t_pipe;

void	handle_signal(int signum);
void	handle_running_signal(int signum);
void	handle_heredoc_signal(int signum);
bool	contain_wildcard(char *str);
void	bubble_sort(char ***arr, int n);
bool	is_eqlvar(char *envvar, char *varname);
void	expand(char **lex, t_ctx *ctx);
char	*expand_heredoc(char **content, t_ctx *ctx);
void	ft_strnjoin(char **result, char *str, size_t len, t_ctx *ctx);
void	double_chunk(char **end, char **result, t_ctx *ctx);
void	single_chunk(char **end, char **result, t_ctx *ctx);
void	plain_chunk(char **end, char **result, t_ctx *ctx);
void	expand_variable(char **end, t_ctx *ctx, char **result);
void	expand_variable_blanks(char **end, t_ctx *ctx, char **result);
void	get_value(char **end, t_ctx *ctx, char **value);
void	collect_single_chars(char **end, char **result, t_ctx *ctx);
void	collect_double_chars(char **end, char **result, t_ctx *ctx);
bool	is_valid_varname(char *c);
bool	is_plain(char *c);

bool	is_directory(char *pathname);
void	handle_wildcard(t_node *node, char **input);
bool	contain_wildcard(char *str);
void	expand_wildcard(t_node *node, char *pattern, char ***result);
void	setup_signals(int mode, void *ctx);
void	restore_stdfd(int stdfd, t_node *node);
void	process_filename(t_node *node);
void	error(int exitcode, t_ctx *ctx, t_m msg);
pid_t	efork(t_node *node);
void	eexecve(char *pathname, t_node *node);
char	*get_cmdname(void *node);
int		eopen(char *pathname, int flags, int mode, t_node *node);
void	edup2(int oldfd, int newfd, t_node *node);

char	**get_var(t_ctx *ctx, char *varname);
char	*get_val(t_ctx *ctx, char *varname);
char	*get_val_exitcode(t_ctx *ctx);
void	add_var(t_node *node, char *str);
int		init_ctx(t_ctx **ctx, char **envp);

void	process_and(t_node	*node);
void	process_or(t_node	*node);

int		allclean(t_node *node, int mode);

void	add_stash(char *arg, t_node *node);
char	*pop_stash(t_node *node);

void	run_cmd(t_node *node);
char	*get_pathname(t_node *node);

int		get_exitcode(pid_t pid);
bool	is_exist(char *pathname);
bool	is_executable(char *pathname);
bool	is_pathname(char *cmd);
bool	is_ambiguous(char **stash);
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
void	prompt(int argc, char **argv, char **envp);

// -- PARSING --
t_node	*parse(char *statement, t_ctx *ctx);
// -- LEXER --
t_tok	*lexer(char *statement, t_ctx *ctx);
t_tok	*init_token(char *start, int len, t_ctx *ctx);
t_type	typify_token(char *lex);
void	add_token(t_tok *new, t_tok **head, t_tok **cur);
void	tokenize_words(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_operators(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_parenthesis(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_vertical_bar(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_ampersand(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_angles(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_quotes(char **lex, t_ctx *ctx);
void	tokenize_heredoc(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx);
void	tokenize_content(char *delim, t_ctx *ctx, t_tok **tokens, t_tok **current);
bool	get_valid_delim(char **delim, t_ctx *ctx, t_tok **current, bool *quotes);
void	attach_token(char *content, t_ctx *ctx, t_tok **tokens, t_tok **current);
char	*get_delimeter(char **lexeme, t_ctx *ctx);
void	single_string(char **end, t_ctx *ctx);
void	double_string(char **end, t_ctx *ctx);
void	skip_blanks(char **lex);
bool	is_open_parenthesis(char *lex);
bool	is_close_parenthesis(char *lex);
bool	is_vertical_bar(char *lex);
bool	is_less(char *lex);
bool	is_greater(char *lex);
bool	is_ampersand(char *lex);
bool	is_double_ampersand(char *lex);
bool	is_asterisk(char *lex);
bool	is_dollar(char *lex);
bool	is_single_quote(char *lex);
bool	is_double_quote(char *lex);
bool	is_blank(char *lex);
bool	is_character(char *lex);
bool	is_word_lexeme(char *lex);
bool	is_operator(char *lex);
bool	is_queston(char *c);
// -- SYNTAXER --
t_node	*syntaxer(t_tok *tok, t_ctx *ctx);
t_node	*init_node(t_tok *tok, t_node *left, t_node *right, t_ctx *ctx);
t_node	*parse_list(t_tok **tok, t_ctx *ctx);
t_node	*parse_pipeline(t_tok **tok, t_ctx *ctx);
t_node	*parse_group(t_tok **tok, t_ctx *ctx);
t_node	*parse_expression(t_tok **tok, t_ctx *ctx);
void	collect_args(t_tok **tok, t_node *word, t_ctx *ctx);
t_node	*parse_redir(t_tok **tok, t_ctx *ctx);
t_node	**stack_redirs(t_tok **tok, t_node **stack, int *elem, t_ctx *ctx);
t_node	*unfold_redirs(t_node **stack, int *elem, t_node *node);
bool	is_group_close(t_tok *tok);
bool	is_group_open(t_tok *tok);
bool	is_andor(t_tok *tok);
bool	is_pipe(t_tok *tok);
bool	is_redir(t_tok *tok);
bool	is_word_token(t_tok *tok);
void	step_forward(t_tok **tok);
// -- CLEAN --
char	*parserror(char *type, char *lex, int code, t_ctx *ctx);
t_node	*rule_error(t_tok **token, t_ctx *ctx);
void	*tok_error(char *lexeme, t_ctx *ctx);
void	clean_tokens(t_tok *tok);
void	clean_tree(t_node *node);
// -- PRINTER --
void	print_tok(t_tok *tok);
void	print_node(t_node *ast, int depth);
void	save_tree(t_node *node);

#endif