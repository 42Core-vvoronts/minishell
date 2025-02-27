/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:22:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 09:59:03 by vvoronts         ###   ########.fr       */
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
	char prompt[] = "minishell$ ";
    while (true)
    {
		setup_signals(IS_PROMPT, ctx);
        statement = readline(prompt);
		if (g_signal != SIGNO)
		{
			ctx->exitcode = g_signal + 128;
			g_signal = SIGNO;
		}
		setup_signals(IS_RUNNING, ctx);
        if (!statement)
        {
			ft_memset(&node, 0, sizeof(t_node));
			node.ctx = ctx;
			run_exit(&node);
		}
		add_history(statement); //not add if NULL?
        ast = parse(statement, ctx);
		if (ast)
			evaluate(ast);
        free(statement);
		if (g_signal == SIGQUIT && ctx->exitcode != EXIT_SUCCESS)
		{
			write(STDOUT_FILENO, "Quit\n", 5);
		}
		// printf("exitcode: %d\n", ctx->exitcode);
    }
}

