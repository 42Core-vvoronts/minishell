/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 15:29:37 by vvoronts         ###   ########.fr       */
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
t_node *parse_redir(t_tok **tok)
{
    if (!*tok)
        return NULL;

    t_tok *op_tok = *tok;
    t_type op = op_tok->type;
    *tok = (*tok)->next;  // consume the redirection operator

    if (!*tok || !is_word(*tok))
    {
        fprintf(stderr, "Error: expected a word after redirection operator '%s'\n",
                op_tok->lexeme);
        return NULL;
    }
    t_tok *word_tok = *tok;
    *tok = (*tok)->next;  // consume the word

    /* Create a redirection node where the file operand is attached as the left child */
    return init_node(op, op_tok->lexeme, init_node(word_tok->type, word_tok->lexeme, NULL, NULL), NULL);
}