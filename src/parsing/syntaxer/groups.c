/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 18:24:42 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_group_open(t_tok *tok)
{
	if (tok && tok->type == GROUP && is_eqlstr(tok->lexeme, "("))
		return (true);
	return (false);
}

bool	is_group_close(t_tok *tok)
{
	if (tok && tok->type == GROUP && is_eqlstr(tok->lexeme, ")"))
		return (true);
	return (false);
}

/**
 *  * 
 * @brief Syntax rule <group> ::= '(' <list> ')'
 * 
 * @param tok The token list
 * @return pointer to the new AST node
 * 
 * The parser expects a lexeme of "(" and later a lexeme of ")".
 * Example: (ls && (cat || grep))
 *
 *        ()          <-- Group #1
 *       /    
 *      &&  
*     /    \
*  ls       ()		  <-- Group #2
*          /  
*  		 ||
*       /  \
*     cat  grep
* 
*/
t_node	*parse_group(t_tok **token, t_ctx *ctx)
{
	t_node	*node;
	t_tok	*operator;

	if (!*token)
		return (NULL);
	if (is_group_open(*token))
	{
		operator = *token;
		step_forward(token);
		if (!*token || is_group_close(*token))
			return (rule_error(token, ctx));
		if (is_group_open(*token))
			node = parse_group(token, ctx);
		else
			node = parse_list(token, ctx);
		if (!is_group_close(*token))
			return (rule_error(token, ctx));
		step_forward(token);
		return (init_node(operator, node, NULL, ctx));
	}
	else
		return (rule_error(token, ctx));
}
