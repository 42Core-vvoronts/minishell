/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:22:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 19:55:07 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int minishell(int argc, char **argv, char **envp)
{
    char	*statement;
	t_node	*ast;
	t_ctx	*ctx;
	(void)argc;
	(void)argv;
	(void)envp;
	(void)ast;

	ast = NULL;
	init_ctx(&ctx, envp);
	char prompt[] = "\033[1;32mminishell$ \033[0m";
    while (true)
    {
        statement = readline(prompt);
        if (!statement)
        {
            ft_printf("\n");
            exit(1);
		}
		add_history(statement);
        ast = parse(statement, ctx);
		// if (ast)
		// 	exit(0);
		// evaluate(ast);
        free(statement);
    }
}
