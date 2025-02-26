/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 11:35:21 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse the statement
 *
 * @param statement The statement to parse
 * @param ctx The context
 *
 * <statement> 		::= <list>
 *
 * <list>			::= <pipeline> {('&&' | '||') <pipeline>}*
 *
 * <pipeline> 		::= <expression> { '|' <expression> }*
 *
 * <expression> 	::= {<word> | <redirection>}*
 * 	     			  | <group> <redirection>*
 *
 * <group> 			::= '(' <list> ')'
 *
 * <redirection>	::=  '>' <word>
 *              	  |  '<' <word>
 *               	  |  '>>' <word>
 *                	  |  '<<' <word>
 *
 * <word> 			::= 'characters'
 *
 * @return The abstract syntax tree
 *
 */
t_node	*parse(char *statement, t_ctx *ctx)
{
	t_tok	*tokens;
	t_node	*ast;

	tokens = lexer(statement, ctx);
	ast = syntaxer(tokens, ctx);
	ctx->head = ast;
	//printer
	// if (ast)
	// 	save_tree(ast);
	return (ast);
}
