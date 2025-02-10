/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 14:29:39 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type typify(char *lexeme) 
{
	if (is_eqlstr(lexeme, "&&"))
		return AND;
	if (is_eqlstr(lexeme, "||"))
		return OR;
	if (is_eqlstr(lexeme, "(") || is_eqlstr(lexeme, ")"))
		return GROUP;
	if (is_eqlstr(lexeme, "|"))
		return PIPE;
    if (is_eqlstr(lexeme, "<"))
		return REDIR_IN;
	if (is_eqlstr(lexeme, ">"))
		return REDIR_OUT;
	if (is_eqlstr(lexeme, ">>"))
		return REDIR_APPEND;
	if (is_eqlstr(lexeme, "<<"))
		return REDIR_HEREDOC;
	return ARGUMENT;
}

void add_token(t_tok *new, t_tok **head, t_tok **current)
{
	if (*head == NULL)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

t_tok *lexer(char *statement)
{
	t_tok *tokens;
	t_tok *current;

	tokens = NULL;
	current = NULL;
    while (*statement)
    {
		skip_spaces(&statement);
		handle_quotes(&statement, &tokens, &current);
		handle_words(&statement, &tokens, &current);
		handle_operators(&statement, &tokens, &current);
    }
    return tokens;
}
// new = init_token(*lexemes);
// add_token(new, &tokens, &current);
// lexemes++;
