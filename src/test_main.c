#include "minishell.h"

int g_signal;

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
	setup_signals(IS_PROMPT, NULL);
	statement = argv[1];
	setup_signals(IS_RUNNING, ctx);
	if (g_signal == SIGINT)
		ctx->exitcode = g_signal + 128;
	if (!statement)
	{
		node.ctx = ctx;
		run_exit(&node);
	}
	add_history(statement);
	ast = parse(statement, ctx);
	if (!ast)
		exit(ctx->exitcode);
	evaluate(ast);
	// free(statement);
	// printf("exitcode: %d\n", ctx->exitcode);
	if (g_signal != SIGNO)
		g_signal = -1;
}
int	main(int argc, char **argv, char **envp)
{
	printf("Test: %s\n", argv[1]);
	prompt(argc, argv, envp);
	return (EXIT_SUCCESS);
}
