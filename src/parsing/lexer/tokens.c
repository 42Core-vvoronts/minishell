/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inittok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:21:51 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 11:43:38 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Init a new token node
 *
 * @param start The start character of the lexeme
 * @param len The length of the lexeme
 * @param ctx The context

 * @return pointer to the new node
 * 
 */
t_tok	*init_token(char *start, int len, t_ctx *ctx)
{
	t_tok	*token;
	

	token = ft_calloc(1, sizeof(t_tok));
	if (!token)
		error(-1, ctx, (t_m){strerror(errno), NULL});
	token->lexeme = ft_strndup(start, len);
	token->type = typify_token(token->lexeme);
	token->next = NULL;
	return token;
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
void add_token(t_tok *new, t_tok **head, t_tok **current)
{
	if (*head == NULL)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

t_type typify_token(char *lexeme) 
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
