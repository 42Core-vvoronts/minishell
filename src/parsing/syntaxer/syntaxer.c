/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:37:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/23 11:22:04 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void step_forward(t_tok **token)
{
	if (*token)
    	*token = (*token)->next;
}

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
 * @brief Used by create_tree() to decide what to parse first.
 * 
 * It handles either a group or an expression grammar rule.
 * 
 * @param tok The token list
 * @return pointer to the root node of the tree
 */
t_node	*group_or_expression(t_tok **tok, t_ctx *ctx)
{
    if (!*tok || (*tok)->lexeme)
        return NULL;
    if (is_group_open(*tok))
        return parse_group(tok, ctx);
    else
        return parse_expression(tok, ctx);
}

/**
 * @brief Recursive descent with precedence climbing
 *  
 * This function starts by parsing a group or simple expression, then iterates
 * through tokens, recursively handling operators with higher or equal precedence.
 * It builds an AST node for each operator, ensuring correct operator associativity.
 *
 * @param tok Pointer to the token list.
 * @param precedence Current operator precedence level.
 * @param ctx Parsing context.
 * @return Pointer to the root node of the AST.
 * 
 */
t_node	*create_tree(t_tok **tok, int precedence, t_ctx *ctx)
{
    t_node	*left;
	t_node	*right;
	t_type	operator;
	t_tok	*token;

	left = group_or_expression(tok, ctx);
	if (!left)
		return NULL;
    while (*tok && get_precedence((*tok)->type) >= precedence)
    {
        operator = (*tok)->type;
        precedence = get_precedence(operator);
		token = *tok;
		step_forward(tok);
		right = create_tree(tok, precedence + 1, ctx);
        left = init_node(operator, token->lexeme, left, right, ctx);
    }
    return left;
}

/**
 * @brief Creates AST from token list. Syntaxer entry point.
 * 
 * Starts from list grammar rule.
 * 
 * @param tokens The token list
 * @param ctx The context
 * 
 * @return pointer to the root node of the tree
 */
t_node *syntaxer(t_tok *tokens, t_ctx *ctx)
{
	t_node *ast;

	ast = NULL;
	if (tokens)
		ast = parse_list(&tokens, ctx);
	return (ast);
}
