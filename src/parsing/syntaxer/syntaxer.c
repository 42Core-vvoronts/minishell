/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:37:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 18:14:22 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
t_node	*syntaxer(t_tok *tokens, t_ctx *ctx)
{
	t_node	*ast;

	ast = NULL;
	if (!tokens)
		return (ast);
	ctx->errsyn = false;
	ast = parse_list(&tokens, ctx);
	if (ctx->errsyn == true || tokens)
		return (rule_error(&tokens, ctx, ast));
	ctx->head = ast;
	return (ast);
}

void	step_forward(t_tok **token)
{
	if (*token)
		*token = (*token)->next;
}
