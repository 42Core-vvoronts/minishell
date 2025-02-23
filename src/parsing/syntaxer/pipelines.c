/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:35 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/23 10:48:42 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pipe(t_tok *tok)
{
	if (tok && tok->type == PIPE)
		return true;
	return false;
}

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
t_node	*parse_pipeline(t_tok **tok, t_ctx *ctx)
{
	t_node	*root;
	t_node	*left;
	t_node	*right;
	t_tok	*operator;

	left = parse_expression(tok, ctx);
	if (is_pipe(*tok))
	{
		operator = *tok;
		step_forward(tok);
		right = parse_pipeline(tok, ctx);
		if (!right)
		{
			// error(2, ctx, (t_m){"syntax error near unexpected token"});
			return NULL;
		}
		root = init_node(operator->type, operator->lexeme, left, right, ctx);
		return root;
	}
	return left;
}

