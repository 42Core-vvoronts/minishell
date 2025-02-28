/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wraperror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:07:01 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 14:17:44 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*rule_error(t_tok **token, t_ctx *ctx, t_node *node)
{
	if (node)
		clean_tree(node);
	if (ctx->errsyn == false)
	{
		ctx->errsyn = true;
		if (*token)
			return ((t_node *)parserror("syntax", (*token)->lexeme, 2, ctx));
		return ((t_node *)parserror("syntax", "newline", 2, ctx));
	}
	return (NULL);
}

void	*tok_error(char *lexeme, t_ctx *ctx)
{
	char	*tmp;

	tmp = lexeme;
	clean_tokens(ctx->headtok);
	ctx->headtok = NULL;
	if (ctx->errlex == false)
	{
		ctx->errlex = true;
		if (*tmp)
			return ((t_node *)parserror("syntax", tmp, 2, ctx));
		return ((t_node *)parserror("syntax", "newline", 2, ctx));
	}
	return (NULL);
}

char	*parserror(char *type, char *lexeme, int code, t_ctx *ctx)
{
	char	*msg;

	if (is_eqlstr(type, "syntax"))
		msg = "syntax error near unexpected token";
	else
		msg = type;
	if (lexeme)
		error(code, ctx, (t_m){msg, lexeme + TOK});
	else
		error(code, ctx, (t_m){msg, NULL});
	return (NULL);
}
