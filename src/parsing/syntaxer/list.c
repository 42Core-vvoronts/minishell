/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/06 19:11:41 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Synatax rule: <list> ::= <pipeline> {('&&' | '||') <pipeline>}*
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
t_node	*parse_list(t_tok **tok)
{
	t_node	*left;
	t_node	*right;
	t_tok	*operator;
	t_type	type;
	
	left = parse_pipe(tok);
	while (*tok && ((*tok)->type == AND || (*tok)->type == OR))
	{
		type = (*tok)->type;
		operator = *tok;
		*tok = (*tok)->next;
		right = parse_pipe(tok);
		left = new_node(type, operator->lexeme, left, right);
	}
	return left;
}
