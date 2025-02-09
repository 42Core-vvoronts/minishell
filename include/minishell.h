/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/09 16:45:53 by vvoronts         ###   ########.fr       */
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
	WORD,
	CONTENT
}	t_type;

typedef struct s_ctx
{
	char	**envp;
	char	*ttyname;
	char	**stash;
	int		*opened_fd;
	pid_t	exitcode;
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

void	process_and(t_node	*node);
void	process_or(t_node	*node);

void	add_arg(char *arg, char * **stash);
char	*pop_arg(char * **stash);
char 	**get_argv(char * **args);

void 	run_cmd(t_node *node);

int		get_exitcode(pid_t pid);


void	process_group(t_node *node);


void	process_pipe(t_node *node);
int		open_pipe(t_pipe *p);
int		close_pipe(t_pipe *p);

void	process_redir_append(t_node *node);
void	process_redir_heredoc(t_node *node);
void	process_redir_in(t_node *node);
void	process_redir_out(t_node *node);

void	process_word_zero_quotes(t_node *node);
void	process_word_single_quotes(t_node *node);
void	process_word_double_quotes(t_node *node);

void	evaluate_node(t_node *node);


// -- PARSING --
t_node	*parse(char *input);

// -- LEXER --
t_tok	*lexer(char *cmdline);
t_type	typify(char *lexeme);
bool	is_not_space(char symbol);

// -- SYNTAXER --
t_node	*syntaxer(t_tok *tok);
t_node	*group_or_expression(t_tok **tok);
// syntax tree
t_node	*create_tree(t_tok **tok, int precedence);
t_node	*init_node(t_type type, const char *token, t_node *left, t_node *right);
int		get_precedence(t_type type);
// list
t_node	*parse_list(t_tok **tok);
// pipe
t_node	*parse_pipeline(t_tok **tok);
// expression
t_node	*parse_expression(t_tok **tok);
int		is_word(t_tok *tok);
// group
t_node	*parse_group(t_tok **tok);
int		is_group_close(t_tok *tok);
int		is_group_open(t_tok *tok);
// redirecion
t_node	*parse_redir(t_tok **tok);
int		is_redir(t_tok *tok);
// utils
void	step_forward(t_tok **tok);
// errors
void	*error_exit(char *msg);




// -- PRINTER --
int minishell(int argc, char **argv, char **envp);
void print_tokens(t_tok *tokens);
void print_node(t_node *ast, int depth);
void save_tree(t_node *node);

#endif
