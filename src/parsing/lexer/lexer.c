/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 11:05:05 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *lexer(char *statement)
{
	t_tok *tokens;
	t_tok *current;

	tokens = NULL;
	current = NULL;
    while (*statement)
    {
		skip_spaces(&statement);
		tokenize_quotes(&statement, &tokens, &current);
		tokenize_words(&statement, &tokens, &current);
		tokenize_operators(&statement, &tokens, &current);
    }
    return tokens;
}
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

bool	is_operator(char *lexeme)
{
	if (is_greater(lexeme) || is_less(lexeme) ||
		 is_vertical_bar(lexeme) || is_ampersand(lexeme) ||
		 is_open_parenthesis(lexeme) || is_close_parenthesis(lexeme))
		return true;
	return false;
}

void	tokenize_operators(char **lexeme, t_tok **tokens, t_tok **current)
{
	if (!*lexeme)
		error_exit("end of statement");
	if (is_open_parenthesis(*lexeme) || is_close_parenthesis(*lexeme))
		tokenize_parenthesis(lexeme, tokens, current);
	else if (is_less(*lexeme))
	{
		char *next;
		next = lexeme[1];
		if (next && is_less(next))
			tokenize_heredoc(lexeme, tokens, current);
		tokenize_angles(lexeme, tokens, current);
	}
	else if (is_greater(*lexeme))
		tokenize_angles(lexeme, tokens, current);
	else if (is_vertical_bar(*lexeme))
		tokenize_vertical_bar(lexeme, tokens, current);
	else if (is_ampersand(*lexeme))
		tokenize_ampersand(lexeme, tokens, current);
}
