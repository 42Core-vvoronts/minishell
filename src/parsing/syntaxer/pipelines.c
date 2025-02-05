/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:35 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/05 18:10:13 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the PIPE operator
 * 
 * <pipeline> ::= <exec> { '|' <exec> }*
 * 
 * @param tok The token list.
 * @return New left node
 */
t_node *parse_pipe(t_tok **tok)
{
    t_node *left = parse_word(tok);

    while (*tok && ((*tok)->type == PIPE))
    {
        t_tok *op_tok = *tok;
        *tok = (*tok)->next;  // consume the PIPE

        t_node *right = parse_word(tok);
        left = new_node(PIPE, op_tok->lexeme, left, right);
    }
    return left;
}