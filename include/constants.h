/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:53 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/13 18:14:29 by vvoronts         ###   ########.fr       */
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

typedef enum e_cmd
{
	EXEC,
	REDIRECTION,
	PIPE,
// LIST, for ;
// BACK
}	e_cmd;

typedef enum e_label
{
    PIPETOK,       // '|'
    LITERAL,       // General word (letters, digits, '_')
	
    INPUT,         // '<'
    OUTPUT,        // '>'
    APPEND,        // '>>'
    HEREDOC,       // '<<'
    ENV_VAR,       // '$<word>'
    STATUS_VAR,    // '$?'
    QUOTE_SINGLE,  // '\''
    QUOTE_DOUBLE,  // '"'
    BUILTIN,       // Builtins like "echo", "cd", etc.
    ASSIGNMENT,    // '<word>=<word>'
    PATH,          // Absolute or relative path
    ERROR,         // Invalid characters
    END            // End of input
} e_label;

typedef struct s_tok
{
	e_cmd			type;
	e_label			label;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;

typedef struct s_ast
{
	e_cmd 		type;
	t_tok		*tok;
	char		*cmd;
	char		*args;
	struct s_ast		*left;
	struct s_ast		*right;
} t_ast;



#endif
