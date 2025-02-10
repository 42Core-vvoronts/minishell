/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 18:20:53 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_tok *tok)
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
	t_node	*word;
	t_type	op;
	
	if (!*tok)
		return NULL;

	operator = *tok;
	op = operator->type;
	step_forward(tok);
	
    if (!*tok || !is_word_token(*tok))
    {
		error_exit("expected a word after operator: redirection");
		return NULL;
    }
	word_tok = *tok;
	step_forward(tok);
	if (op == REDIR_HEREDOC)
		word = init_node(CONTENT, word_tok->lexeme, NULL, NULL, ctx);
	else
		word = init_node(FILENAME, word_tok->lexeme, NULL, NULL, ctx);

    // Create a redirection node where the file is the left child
    return init_node(op, operator->lexeme, word, NULL, ctx);
}