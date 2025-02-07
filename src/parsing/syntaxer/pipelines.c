/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:35 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 10:30:59 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the PIPE operator
 * 
 * <pipeline> ::= <exec> {'|' <exec>}*
 * This rule is right–recursive. For example, given three expressions:
 * 
 * @param tok The token list.
 * @return New left node
 *
 * $ ls | cat | grep
 * 
 *         PIPE          <-- pipe #1
 *         /    \
 *      ls       PIPE     <-- pipe #2
 *              /    \
 *            cat    grep
 */
// t_node	*parse_pipe(t_tok **tok)
// {
//     t_node	*left;
//     t_node	*right;
//     t_tok	*operator;
	
// 	left = parse_expression(tok);

//     while (*tok && ((*tok)->type == PIPE))
//     {
//         operator = *tok;
//         *tok = (*tok)->next;

//         right = parse_expression(tok);
//         left = new_node(PIPE, operator->lexeme, left, right);
//     }
//     return left;
// }
t_node *parse_pipe(t_tok **tok)
{
    t_node *left = parse_expression(tok);
    if (*tok && (*tok)->type == PIPE)
    {
        t_tok *operator = *tok;
        *tok = (*tok)->next;
        t_node *right = parse_pipe(tok);
        return new_node(PIPE, operator->lexeme, left, right);
    }
    return left;
}
