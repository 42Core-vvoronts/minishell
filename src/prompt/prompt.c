/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:22:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/15 11:39:00 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	handle_shlvl(t_ctx *ctx)
{
	char	**var;
	int		lvl;
	char	*lvlvar;
	char	*result;
	t_node	node;

	node.ctx = ctx;
	lvl = 0;
	var = get_var(ctx, "SHLVL");
	lvlvar = "";
	if (var)
		lvlvar = get_val(ctx, "SHLVL");
	ft_atoi(lvlvar, &lvl, sizeof(int), 10);
	lvl++;
	result = ft_strjoin("SHLVL=", ft_itoa(lvl));
	if (!result)
		error(-1, ctx, (t_m){strerror(errno)});
	add_var(&node, result);
	free(result);
}

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
	handle_shlvl(ctx);
	g_signal = SIGNO;
	char prompt[] = "\033[1;32mminishell$ \033[0m";
    while (true)
    {

		setup_signals(IS_PROMPT, NULL);
        statement = readline(prompt);
		setup_signals(IS_RUNNING, ctx);
        if (!statement)
        {
			node.ctx = ctx;
			run_exit(&node);
		}
		add_history(statement); //not add if NULL?
        ast = parse(statement, ctx);
		if (!ast)
			exit(ctx->exitcode);
		evaluate(ast);
        free(statement);
		if (g_signal != SIGNO)
		{
			ctx->exitcode = g_signal + 128;
			g_signal = -1;
		}
		printf("exitcode: %d\n", ctx->exitcode);

    }
}
/* Testcases

( < infiles/inordinary ls / | cat | grep a && ls ) > outfiles/outordinary

*/
