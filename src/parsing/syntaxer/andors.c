/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   andor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/05 18:09:56 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle logical operators
 * 
 * <list> ::= <pipeline> {('&&' | '||') <pipeline>}*
 * 
 * @param tok The token list.
 * @return New left node
 */
t_node *parse_andor(t_tok **tok)
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
