/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:53 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/20 17:09:54 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H


// -- TOKEN --
typedef enum e_quotes_type
{
	BARE,
	SINGLE,
	DOUBLE
} t_quotes_type;

typedef enum t_type
{
	AND,
	OR,
	LPAR,
	RPAR,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_type;

typedef enum e_error
{
	MALLOC,
	CMD_NOT_FOUND,
	ERRNO,
	FORK,
	OPEN,
	DUP2,
	GNL,
	FILE_NOT_FOUND,

}	t_error;

// typedef enum t_type
// {
// 	AND,
// 	OR,
// 	GROUP_OPEN,
// 	GROUP_CLOSE,
//     PIPE,
//     REDIR,
//     HEREDOC,
// 	COMMAND,
//     ARGUMENT,
// 	DOUBLE_QUOTE,
// 	SINGLE_QUOTE,
// 	VARIABLE
// } t_type;

typedef struct s_tok
{
	t_type			type;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;
// typedef struct s_tok
// {
// 	t_type			type;
// 	char			*start;
// 	char			*end;
// 	struct s_tok	*next;
// } t_tok;

// -- AST --
typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}	t_args;

typedef struct s_ast
{
	t_type			type;
	char			*token;
	t_args			*args;
	struct s_ast	*left;
	struct s_ast	*right;
} t_ast;

typedef struct s_pipe
{
	int read;
	int write;
} t_pipe;

typedef struct s_ctx
{
	char **envp;
	char *ttyname;
	char **argv;
} t_ctx;

// -- CONTEXT/META --
// typedef struct s_meta
// {
// 	current token;
// 	ast;
// 	stdin??
// 	stdout??
// 	stderr??
// 	error
// 	child??
// } t_meta;

// -- ERRORS --
// General
#define ERROR_MALLOC "minishell: Malloc cannot allocate memory\n"
#define ERROR_NO_ARGS "minishell: no arguments\n"
// Lexer
#define ERROR_LENGTH_WORD "Error: Word exceeds maximum length\n"
// Syntaxer
#define ERROR_NO_CLOSE_QUOTE "minishell: syntax error: unclosed quotes\n"
#define ERROR_INVALID_TOKEN "syntax error: invalid token\n"
#define ERROR_NEWLINE "minishell: syntax error near unexpected token `newline'\n"

#endif
