/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 10:38:38 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_group_open(t_tok *tok)
{
	if (tok->type == GROUP && ft_strcmp(tok->lexeme, "(") == 0)
		return (1);
	return (0);
}

int is_group_close(t_tok *tok)
{
	if (tok->type == GROUP && ft_strcmp(tok->lexeme, ")") == 0)
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
t_node *parse_group(t_tok **tok)
{
    if (!*tok || ft_strcmp((*tok)->lexeme, "(") != 0)
    {
        fprintf(stderr, "Error: expected '(' at the beginning of group\n");
        return NULL;
    }
    *tok = (*tok)->next;  // consume "("

    t_node *node = parse_list(tok);

    if (!*tok || ft_strcmp((*tok)->lexeme, ")") != 0)
    {
        fprintf(stderr, "Error: expected ')' at the end of group\n");
        return NULL;
    }
    *tok = (*tok)->next;  // consume ")"
    /* Wrap the group in a GROUP node if desired */
    return new_node(GROUP, "()", node, NULL);
}