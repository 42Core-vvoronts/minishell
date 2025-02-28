/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 14:29:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief tokenizes the statement and check lexemes validity
 *
 * @param statement initial string of lexemes
 * 
 * Fucntion goes through the statement and uses helper fucntions 
 * for each type of character
 * 
 * @return pointer on the list of lexicaly valid tokens
 */
t_tok	*lexer(char *statement, t_ctx *ctx)
{
	t_tok	*tokens;
	t_tok	*current;

	tokens = NULL;
	current = NULL;
	ctx->headtok = tokens;
	ctx->errlex = false;
	while (statement && *statement && !ctx->errlex)
	{
		skip_blanks(&statement);
		tokenize_words(&statement, &tokens, &current, ctx);
		tokenize_operators(&statement, &tokens, &current, ctx);
	}
	if (ctx->errlex == true)
	{
		clean_tokens(ctx->headtok);
		ctx->headtok = NULL;
		return (NULL);
	}
	return (tokens);
}

/**
 * @brief Add a new token to the list
 *
 * @param new The new token
 * @param head The head of the list
 * @param current The current node of the list

* @return void
*
* @note Side effect: moves pointer to the current last node (new one)
* 
*/
void	add_token(t_tok *new, t_tok **head, t_tok **current)
{
	if (!new)
	{
		current = NULL;
		return ;
	}
	else if (*head == NULL)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

t_type	typify_token(char *lexeme)
{
	if (is_eqlstr(lexeme, "&&"))
		return (AND);
	if (is_eqlstr(lexeme, "||"))
		return (OR);
	if (is_eqlstr(lexeme, "(") || is_eqlstr(lexeme, ")"))
		return (GROUP);
	if (is_eqlstr(lexeme, "|"))
		return (PIPE);
	if (is_eqlstr(lexeme, "<"))
		return (REDIR_IN);
	if (is_eqlstr(lexeme, ">"))
		return (REDIR_OUT);
	if (is_eqlstr(lexeme, ">>"))
		return (REDIR_APPEND);
	if (is_eqlstr(lexeme, "<<"))
		return (REDIR_HEREDOC);
	return (ARGUMENT);
}
