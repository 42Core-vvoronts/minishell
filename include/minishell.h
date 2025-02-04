/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/04 07:35:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "constants.h"
# include "../lib/elibft/include/elibft.h"

# include <ctype.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <string.h>    // strlen
# include <stdlib.h>    // exit
# include <unistd.h>    // syscalls
# include <readline/readline.h>
# include <readline/history.h>

# define REDIR_FAIL 1

typedef enum t_type
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
	REDIR_HEREDOC_QUOTES,
	REDIR_HEREDOC_NOQUOTES
}	t_type;

typedef struct s_ctx
{
	char **envp;
	char *ttyname;
	char **stash;
	int	*opened_fd;
	pid_t exitcode;
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


// -- INIT --

// -- PROMPT --

// -- PARSING --
// t_ast	*parsing(char *input);
// // Lexer
// t_tok *lexer(char *cmdline);
// // e_cmd typify(e_label label);
// t_type label(char *lexeme);
// bool is_not_space(char symbol);
// // Syntaxer
// t_ast *syntax(t_tok *tok);
// t_ast *create_tree(t_tok **tok);
// t_ast *addnode(t_tok *tok);

// // -- EXPANSION --

// // -- ENVAR --

// // -- EXECUTION --

// // -- SIGNALS --

// // -- ERROR --


// //execution
// int run_cmd(t_ctx *ctx, char **argv);
// char *get_validpath(t_ctx *ctx, char **argv);
// char *get_varvalue(t_ctx *ctx, char *varname);

// //redirection
// int	redir_in(char *pathname);

// //error
// void error(t_ctx *ctx, t_error error);

// // DELETE
// void print_tokens(t_tok *tokens);
// void print_ast(t_ast *ast, int depth);

#endif
