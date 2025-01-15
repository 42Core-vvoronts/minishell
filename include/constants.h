/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:53 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/15 18:17:17 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// char WHITESPACE[] = " \t\n\r\v\f";

// Bastein's structs
/* typedef enum e_type
{
	WORD = 1,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
}							t_type; 
typedef enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
}*/

// typedef enum e_cmd
// {
// 	EXEC,
// 	REDIR,
// 	PIPE,
// // LIST, for ;
// // BACK
// }	e_cmd;

typedef enum e_type
{
	GROUP, 		// '(' ')'
	AND, 
	OR,
    PIPE,       // '|'
    INPUT,         // '<' Redir
    OUTPUT,        // '>' Redir
    APPEND,        // '>>' Redirm
    HEREDOC,      // '<<'
	EXEC,        // Command
    WORD,       // General word (letters, digits, '_') Literal?
} e_type;

typedef struct s_tok
{
	e_type			type;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;

typedef struct s_ast
{
	e_type		type;
	t_tok		*tok;
	char		*cmd;
	char		*args;
	struct s_ast		*left;
	struct s_ast		*right;
} t_ast;



#endif
