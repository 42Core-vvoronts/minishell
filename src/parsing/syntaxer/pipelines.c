/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:35 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 18:30:55 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pipe(t_tok *tok)
{
	if (tok && tok->type == PIPE)
		return (true);
	return (false);
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
	if (is_pipe(*tok) && left)
	{
		operator = *tok;
		step_forward(tok);
		right = parse_pipeline(tok, ctx);
		if (!right)
			return (rule_error(tok, ctx));
		root = init_node(operator, left, right, ctx);
		return (root);
	}
	return (left);
}
