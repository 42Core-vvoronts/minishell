/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:42 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 17:18:51 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

e_label label(char lexeme)
{
	if (lexeme == ' ')
		return SPACE;
	else if (lexeme == '|')
		return PIPE;
	else if (lexeme == '+' || lexeme == '-' || lexeme == '*' || lexeme == '/')  
		return MATH;
	else if (lexeme == '<' || lexeme == '>')
		return REDIRECTION;
	else
		return LITERAL;
}

e_type typify(e_label label)
{
	if (label == MATH)
		return OPERATOR;
	return WORD;
}

bool is_not_space(char symbol)
{
	return (symbol != ' ');
}

t_tok *lexer(char **lexemes)
{
    t_tok *tokens = NULL;
    t_tok *curtok = NULL;
    t_tok *newtok = NULL;

    // Process each lexeme in the array
    while (*lexemes)
    {
        // Process current lexeme
        newtok = malloc(sizeof(t_tok));
        newtok->lexeme = *lexemes; // *lexemes points to the current lexeme
		newtok->label = label((*lexemes)[0]); // Pass the first character of the lexeme to label()
        newtok->type = typify(newtok->label); // Determine type from the label
        newtok->next = NULL;

        if (tokens == NULL)
            tokens = newtok; // First token
        else
            curtok->next = newtok; // Append to the list

        curtok = newtok; // Move to the last token in the list

        lexemes++; // Move to the next lexeme
    }

    return tokens;
}

