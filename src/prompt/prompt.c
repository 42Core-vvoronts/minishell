/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:22:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/11 12:58:16 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(int argc, char **argv, char **envp)
{
    char	*statement;
	t_node	*ast;
	t_ctx	*ctx;
	t_node	node;
	(void)argc;
	(void)argv;
	(void)envp;
	(void)ast;
	(void)ctx;
	(void)statement;

	init_ctx(&ctx, envp);
	char prompt[] = "\033[1;32mminishell$ \033[0m";
    while (true)
    {
        statement = readline(prompt);
        if (!statement)
        {
			node.ctx = ctx;
			run_exit(&node);
		}
		add_history(statement);
        ast = parse(statement, ctx);
		// if (ast)
		// 	exit(0);
		evaluate(ast);
        free(statement);
		// if (g_signal != SIGNO)
		// 	ctx->exitcode = g_signal;
		printf("exitcode: %d\n", ctx->exitcode);
    }
}
/* Testcases

( < infiles/inordinary ls / | cat | grep a && ls ) > outfiles/outordinary

*/
