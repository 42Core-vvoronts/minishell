/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/09 19:25:08 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir(t_tok *tok)
{
	if (!tok)
		return (0);
	return (tok->type == REDIR_APPEND ||
			tok->type == REDIR_HEREDOC ||
			tok->type == REDIR_IN ||
			tok->type == REDIR_OUT);
}

/**
 * @brief Handle the redirection operators
 * 
 * <redirection> ::= ( '>' | '<' | '>>' | '<<' ) <word>
 * 
 * @param tok The token list
 * @return new node
 */
t_node *parse_redir(t_tok **tok, t_ctx *ctx)
{
	t_tok	*operator;
	t_tok	*word_tok;
	t_type	op;
	
	if (!*tok)
		return NULL;

	operator = *tok;
	op = operator->type;
	step_forward(tok);
	
    if (!*tok || !is_word(*tok))
    {
		fprintf(stderr, "Error: expected a word after redirection operator '%s'\n",
			operator->lexeme);
		return NULL;
    }
	word_tok = *tok;
	step_forward(tok);

    // Create a redirection node where the file is the left child
    return init_node(op, operator->lexeme, init_node(word_tok->type, word_tok->lexeme, NULL, NULL, ctx), NULL, ctx);
}