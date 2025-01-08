/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:15:53 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 18:53:04 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


// Bastein's structs
/* typedef enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
}							t_token_type; */



typedef enum e_type
{
	WORD,
	OPERATOR
} e_type;

typedef enum e_label
{
	LETTER,
	DIGIT, // 0-9

	
	SPACE, // whitespace
	MATH,
	COMMAND, // cat, ls 
	LITERAL, // string
	ARGUMENT, // ??
	PIPE, // |
	REDIRECTION // < >
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
