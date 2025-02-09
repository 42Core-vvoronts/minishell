/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/09 19:10:08 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_group_open(t_tok *tok)
{
	if (tok->type == GROUP && is_eqlstr(tok->lexeme, "("))
		return (1);
	return (0);
}

int is_group_close(t_tok *tok)
{
	if (tok->type == GROUP && is_eqlstr(tok->lexeme, ")"))
		return (1);
	return (0);
}

/**
 * @brief Handle the parentheses
 * 
 * <group> ::= '(' <list> ')'
 * 
 * The parser expects a lexeme of "(" and later a lexeme of ")".
 * 
 * @param tok The token list
 * @return new node
 */
t_node *parse_group(t_tok **tok, t_ctx *ctx)
{
	t_node	*node;

    if (*tok && is_group_open(*tok))
	{
		step_forward(tok);
		node = parse_list(tok, ctx);
		
		if (*tok && is_group_close(*tok))
		{
			step_forward(tok);
			return init_node(GROUP, "()", node, NULL, ctx);
		}
		else
			error_exit("expected ')' at the end of group");
	}
    else
		error_exit("expected '(' at the beginning of group");
	return NULL;
}
