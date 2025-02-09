/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 16:57:53 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int minishell(int argc, char **argv, char **envp)
{
    char	*statement;
	t_node	*ast;
	
	ast = NULL;
	char prompt[] = "\033[1;32mminishell$ \033[0m"; 

    if (argc == 2 || !envp)
    {
        parse(argv[1]);
        // execution();
        return 0;
    }

    while (true)
    {
        statement = readline(prompt);
        if (!statement) 
        {
            ft_printf("\n");
            exit(1);
		}
        // history(statement);   
        ast = parse(statement);
		if (ast)
			exit(0);
        	// execute(ast);
        free(statement);
    }
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

	minishell(argc, argv, envp);
	// add_history("test");
	// collect_heredoc("EOF");

	// t_pipe p;
	// open_pipe(&p, NULL);
	// char *buf = malloc(1000);
	// char str;
	// str = 4;
	// ft_putstr_fd("test line", p.write);
	// write(p.write, &str, 1);
	// int b = read(p.read, buf, 1000);
	// (void)b;

	// char *line = readline("> ");
	// printf("%s", line);
	// (void)line;

	// init_ctx(&ctx, envp);
	// // node = init_testcase_forward(ctx);

	// node->ctx->stash = malloc(sizeof(char *) * 10);
	// node->ctx->stash[0] = "cd";
	// node->ctx->stash[1] = ft_strdup("/home/ivan/perm_not_dir/../../");
	// node->ctx->stash[2] = NULL;
	// node->ctx->stash[3] = ft_strdup("TEST3");
	// node->ctx->stash[4] = NULL;

	// // run_export(node);
	// run_cd(node);

	// // save_tree(node);
	// // evaluate_node(node);
	// // printf("Result VAR: %s\n", get_var(ctx, "PATH"));
	// // printf("Result VAL: %s\n", get_val(ctx, "HOME"));

	// // char *input;

	// // while (1)
	// // {
	// // 	input = readline("prompt: ");
	// // 	add_history(input);
	// // 	rl_on_new_line(); //?????
	// // 	parse(input);
	// // 	init_ctx(&ctx, envp);
	// // 	node = init_testcase_forward(ctx);
	// 	// evaluate_node(node);
	// // 	restore_std(node);
	// printf("exitcode: %d\n", node->ctx->exitcode);
	// }
	// 	allclean(node);
	// save_tree(node);

	// (void)input;

	// //start from process_group? group = init prompt
	// // while (1)
	// // {
	// // 	//get_prompt() / get_tree() //readline here

	// // }
	return (EXIT_SUCCESS);
}
