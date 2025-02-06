/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/06 18:52:58 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *peek_tok(t_tok **cur)
{
    return *cur;
}

t_tok *advance_tok(t_tok **cur)
{
    t_tok *tok = *cur;
    if (tok)
        *cur = tok->next;
    return tok;
}

/**
 * @brief Synatax rule: <list> ::= <pipeline> [('&&' | '||') <pipeline>]*
 * 
 * @param tok The token list.
 * @return New left node
 * 
 * $ ls && cat || grep
 *
 *           OR          <-- pipe #1
 *         /    \
 *     AND        grep     <-- pipe #2
*     /    \
 *  ls    cat
 * 
 */
t_node *parse_list(t_tok **tok)
{
    t_node *left = parse_pipe(tok);

    while (*tok && ((*tok)->type == AND || (*tok)->type == OR))
    {
        t_type op = (*tok)->type;
        t_tok *op_tok = *tok;
        *tok = (*tok)->next;  // consume the operator

        t_node *right = parse_pipe(tok);
        left = new_node(op, op_tok->lexeme, left, right);
    }
    return left;
}
