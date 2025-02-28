/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 14:59:40 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_andor(t_tok *tok)
{
	if (!tok)
		return (0);
	return (tok->type == AND || tok->type == OR);
}

/**
 * @brief Synatax rule: <list> ::= <pipeline> {('&&' | '||') <pipeline>}*
 * 
 * @param tok The token list.
 * @return New left node
 * 
 * Example: ls && cat || grep
 *
 *           OR          <-- logical operator #1
 *         /    \
 *     AND        grep     <-- logical operator #2
*     /    \
*  ls    cat
* 
*/
t_node	*parse_list(t_tok **tok, t_ctx *ctx)
{
	t_node	*left;
	t_node	*right;
	t_tok	*operator;

	left = parse_pipeline(tok, ctx);
	while (*tok && is_andor(*tok) && left)
	{
		operator = *tok;
		step_forward(tok);
		right = parse_pipeline(tok, ctx);
		if (!right)
			return (rule_error(tok, ctx, left));
		left = init_node(operator, left, right, ctx);
	}
	return (left);
}
