/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 14:56:15 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *  * 
 * @brief Syntax rule <group> ::= '(' <list> ')'
 * 
 * @param tok The token list
 * @return pointer to the new AST node
 * 
 * The parser expects a lexeme of "(" and later a lexeme of ")".
 * 
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
t_node *parse_group(t_tok **token, t_ctx *ctx)
{
	t_node	*node;

	if (!*token)
		return NULL;
	if (is_group_open(*token))
	{
		step_forward(token);
		if (!*token)
			return ((t_node *)parserror("syntax", "newline", 2, ctx));	
		else if (is_group_close(*token))
			return ((t_node *)parserror("syntax", (*token)->lexeme, 2, ctx));	
		if (is_group_open(*token))
			node = parse_group(token, ctx);
		else
			node = parse_list(token, ctx);
		if (*token && is_group_close(*token))
		{
			step_forward(token);
			return (init_node(GROUP, "()", node, NULL, ctx));
		}
		else
		{
			if (*token)
				return ((t_node *)parserror("syntax", (*token)->lexeme, 2, ctx));
			return NULL;
		}
	}
	return ((t_node *)parserror("syntax", (*token)->lexeme, 2, ctx));
}

bool	is_group_open(t_tok *tok)
{
	if (tok && tok->type == GROUP && is_eqlstr(tok->lexeme, "("))
		return (1);
	return (0);
}

bool	is_group_close(t_tok *tok)
{
	if (tok && tok->type == GROUP && is_eqlstr(tok->lexeme, ")"))
		return (1);
	return (0);
}
