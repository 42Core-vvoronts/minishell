/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:37:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 15:29:37 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the precedence of the token
 *
 * @param type The type of the token

 * @return int precedence
 * 
 */
int get_precedence(t_type type)
{
	if (type == AND || type == OR)
		return 0;
	if (type == GROUP)
		return 1;
	if (type == PIPE) 
		return 1;
	if (type == REDIR_APPEND || type == REDIR_HEREDOC || type == REDIR_IN || type == REDIR_OUT)
		return 2;
	return 3;
}

/**
 * @brief Init a new tree node
 *
 * @param type The type of the token
 * @param token The token
 * @param left The left node
 * @param right The right node

 * @return t_node* 
 * 
 */
t_node *init_node(t_type type, const char *token, t_node *left, t_node *right)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
		error_exit("malloc");
    node->ctx = NULL;  // You can assign a context if needed
    node->type = type;
    node->token = token ? strdup(token) : NULL;
    node->left = left;
    node->right = right;
    return node;
}

/**
 * @brief Precedence climbing parser
 * 
 * This function builds a binary tree for expressions where the operator
 * precedence and left associativity are handled by recursively parsing
 * the right–hand side with a higher minimum precedence.
 * 
 * @param tok The token list
 * @param precedence 
 * @return pointer to the root node of the tree
 * 
 */
t_node	*create_tree(t_tok **tok, int precedence)
{
    t_node	*left;
	t_node	*right;
	t_type	operator;
	t_tok	*token;

	left = group_or_expression(tok);
    while (*tok && get_precedence((*tok)->type) >= precedence)
    {
        operator = (*tok)->type;
        precedence = get_precedence(operator);

        /* For left associativity, parse the right-hand side with precedence+1 */
		token = *tok;
        *tok = (*tok)->next;  // consume the operator

		right = create_tree(tok, precedence + 1);
        left = init_node(operator, token->lexeme, left, right);
    }
    return left;
}

/**
 * @brief  Is used by create_tree() to decide what to parse.
 * 
 * It handles either a group or an exec command.
 * 
 * @param tok The token list
 * @return pointer to the root node of the tree
 */
t_node	*group_or_expression(t_tok **tok)
{
    if (!*tok || (*tok)->lexeme)
        return NULL;
    if (is_group_open(*tok))
        return parse_group(tok);
    else
        return parse_expression(tok);
}

t_node *syntaxify(t_tok *tok)
{
	t_node *ast;
	
	ast = parse_list(&tok);

    // if (!tok || !is_eqlstr(tok->lexeme, "\n"))
	// 	error("Syntax error: expected newline at end of statement.\n");
	return (ast);
}
