/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:53 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/19 14:34:51 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// -- TOKEN --
typedef enum e_type
{
	AND, 
	OR,
	GROUP,
    PIPE,
    REDIR,
    HEREDOC,
	COMMAND,
    ARGUMENT,
	DOUBLE_QUOTE, 
	SINGLE_QUOTE, 
	VARIABLE
} e_type;

typedef struct s_tok
{
	e_type			type;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;
// typedef struct s_tok
// {
// 	e_type			type;
// 	char			*start;
// 	char			*end;
// 	struct s_tok	*next;
// } t_tok;

// -- AST --
typedef struct s_ast
{
	e_type		type;
	t_tok		*tok;
	char		*cmd;
	char		*args;
	struct s_ast		*left;
	struct s_ast		*right;
} t_ast;

// -- CONTEXT/META --
// typedef struct s_meta
// {
// 	current token;
// 	ast;
// 	stdin??
// 	stdout??
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
