/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:22:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 11:59:36 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

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
	lvlvar = ft_itoa(lvl);
	if (!lvlvar)
		error(-1, ctx, (t_m){strerror(errno)});
	result = ft_strjoin("SHLVL=", lvlvar);
	if (!result)
		error(-1, ctx, (t_m){strerror(errno)});
	free(lvlvar);
	add_var(&node, result);
	free(result);
}

static	void	run(char	*statement, t_ctx *ctx)
{
	t_node	node;
	t_node	*ast;

	if (!statement)
	{
		ft_memset(&node, 0, sizeof(t_node));
		node.ctx = ctx;
		run_exit(&node);
	}
	add_history(statement);
	ast = parse(statement, ctx);
	if (ast)
		evaluate(ast);
	free(statement);
	if (g_signal == SIGQUIT && ctx->exitcode != EXIT_SUCCESS)
		write(STDOUT_FILENO, "Quit\n", 5);
	else if (g_signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void	prompt(int argc, char **argv, char **envp)
{
	char	*statement;
	t_ctx	*ctx;

	(void)argc;
	(void)argv;
	init_ctx(&ctx, envp);
	handle_shlvl(ctx);
	g_signal = SIGNO;
	while (true)
	{
		setup_signals(IS_PROMPT, ctx);
		rl_on_new_line();
		rl_replace_line("", 0);
		statement = readline("minishell$ ");
		if (g_signal != SIGNO)
		{
			ctx->exitcode = g_signal + 128;
			g_signal = SIGNO;
		}
		setup_signals(IS_RUNNING, ctx);
		run(statement, ctx);
	}
}
