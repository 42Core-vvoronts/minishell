/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:35 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/06 18:57:38 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the PIPE operator
 * 
 * <pipeline> ::= <exec> ['|' <exec>]*
 * This rule is right–recursive. For example, given three expressions:
 * 
 * @param tok The token list.
 * @return New left node
 *
 * $ ls | cat | grep a
 * 
 *         PIPE          <-- pipe #1
 *         /    \
 *      ls       PIPE     <-- pipe #2
 *              /    \
 *            cat    grep
 */
t_node	*parse_pipe(t_tok **tok)
{
    t_node	*left;
    t_node	*right;
    t_tok	*operator;
	
	left = parse_expression(tok);

    while (*tok && ((*tok)->type == PIPE))
    {
        operator = *tok;
        *tok = (*tok)->next;  // consume the PIPE

        right = parse_expression(tok);
        left = new_node(PIPE, operator->lexeme, left, right);
    }
    return left;
}

