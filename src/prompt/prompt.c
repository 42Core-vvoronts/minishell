/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:22:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 04:43:07 by ipetrov          ###   ########.fr       */
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
	(void)node;

	setup_signals(IS_IGNORE, NULL);
	init_ctx(&ctx, envp);

	handle_shlvl(ctx);
	g_signal = SIGNO;
	char prompt[] = "bash-5.2$ ";
    while (true)
    {
		setup_signals(IS_PROMPT, ctx);
        statement = readline(prompt);
		setup_signals(IS_RUNNING, ctx);
        if (!statement)
        {
			node.ctx = ctx;
			run_exit(&node);
		}
		add_history(statement); //not add if NULL?
        ast = parse(statement, ctx);
		if (ast)
			evaluate(ast);
        free(statement);
		if (g_signal != SIGNO)
		{
			ctx->exitcode = g_signal + 128;
			g_signal = SIGNO;
		}
		printf("exitcode: %s\n", get_val(ctx, "?"));
    }
}

