/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/07 17:21:06 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parsing(char *cmdline)
{
	t_tok *tokens;
	t_node *ast;

	tokens = lexify(cmdline);
	ast = syntaxify(tokens);

	// printf("\nAST saved in file result_tree.png\n");
	save_tree(ast);
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

