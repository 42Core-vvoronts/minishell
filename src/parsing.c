/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/13 19:43:35 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(char *cmdline)
{
	t_tok *tokens;
	t_ast *ast;

	tokens = lexer(cmdline);
	ast = syntax(tokens);
	
	printf("\nTokens:\n");
	print_tokens(tokens);
	printf("\nAbstract Syntax Tree:\n");
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

	return 0;
}

