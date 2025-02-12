/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 11:00:19 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse(char *statement, t_ctx *ctx)
{
	t_tok	*tokens;
	t_node	*ast;

	tokens = lexer(statement);
	ast = syntaxer(tokens, ctx);
	//printer
	save_tree(ast);
	return ast;
}

