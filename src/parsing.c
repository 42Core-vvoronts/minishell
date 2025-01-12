/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/12 15:02:14 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(char *input)
{
	t_tok *tokens;
	char **lexemes;
	t_ast *ast;

	lexemes = scan(input);
	tokens = lexer(lexemes);
	ast = parse(tokens);
	
	printf("\nTokens:\n");
	print_tokens(tokens);
	printf("\nAbstract Syntax Tree:\n");
	print_ast(ast, 0);


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

