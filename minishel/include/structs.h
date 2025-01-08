/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:53 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 19:36:28 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


// Bastein's structs
/* typedef enum e_type
{
	WORD = 1,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
}							t_type; */



typedef enum e_type
{
	WORD,
	OPERATOR
} e_type;

typedef enum e_label {
    PIPE,          // '|'
    INPUT,         // '<'
    OUTPUT,        // '>'
    APPEND,        // '>>'
    HEREDOC,       // '<<'
    LITERAL,       // General word (letters, digits, '_')
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
	e_type			type;
	e_label			label;
	char			*lexeme;
	struct s_tok	*next;
} t_tok;

typedef struct s_ast
{
	e_label			label;
	char 			operator;
	struct s_ast	*left;
	struct s_ast	*right;
} t_ast;

#endif
