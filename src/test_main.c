#include "minishell.h"

int g_signal;

void	prompt(int argc, char **argv, char **envp)
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

    statement = argv[1];
	if (!statement)
	{
		ft_printf("\n");
		exit(1);
	}
	add_history(statement);
	ast = parse(statement, ctx);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*node;
	t_ctx	*ctx;
	pid_t	pid;

	(void)pid;
	(void)argc;
	(void)argv;
	(void)envp;
	(void)ctx;
	(void)node;

	prompt(argc, argv, envp);
	return (EXIT_SUCCESS);
}
