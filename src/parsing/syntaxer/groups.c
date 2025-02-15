/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/15 08:23:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	is_group_open(t_tok *tok)
{
	if (tok->type == GROUP && is_eqlstr(tok->lexeme, "("))
		return (1);
	return (0);
}

bool	is_group_close(t_tok *tok)
{
	if (tok->type == GROUP && is_eqlstr(tok->lexeme, ")"))
		return (1);
	return (0);
}

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
			error(2, ctx, (t_m){"syntax error: unexpected end of file"});			
		else if (is_group_close(*token))
			error(2, ctx, (t_m){"syntax error near unexpected token", (*token)->lexeme});
		else if (is_group_open(*token))
			return(parse_group(token, ctx));
		else
		{
			node = parse_list(token, ctx);
			if (*token && is_group_close(*token))
			{
				step_forward(token);
				if (!*token)
					error(2, ctx, (t_m){"syntax error near unexpected token", "newline"});
				else
					return init_node(GROUP, "()", node, NULL, ctx);
			}
			else
				error(2, ctx, (t_m){"unexpected EOF while looking for matching", ")"});
		}
	}
	else
		error(2, ctx, (t_m){"syntax error near unexpected token", (*token)->lexeme});
	return NULL;
}
