/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 18:10:41 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_type	type;

	left = parse_pipeline(tok, ctx);
	while (*tok && is_andor(*tok))
	{
		type = (*tok)->type;
		operator = *tok;
		step_forward(tok);
		right = parse_pipeline(tok, ctx);
		if (!right || !left)
			return ((t_node *)parserror("syntax", operator->lexeme, 2, ctx));
		left = init_node(type, operator->lexeme, left, right, ctx);
	}
	return (left);
}

bool	is_andor(t_tok *tok)
{
	if (!tok)
		return (0);
	return (tok->type == AND || tok->type == OR);
}
