/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/20 14:32:16 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *parsing(char *cmdline)
{
	t_tok *tokens;
	t_ast *ast;

	tokens = lexer(cmdline);
	ast = syntax(tokens);

	// printf("\nAbstract Syntax Tree:\n");
	print_ast(ast, 0);

	printf("\n");


	// Clean up
	t_tok *temp;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}

	return ast;
}

