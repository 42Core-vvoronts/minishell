/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 19:05:13 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_ctx(t_ctx **ctx, char **envp)
{
	*ctx = malloc(sizeof(t_ctx));
	
	(*ctx)->envp = envp;
	(*ctx)->ttyname = NULL;
	(*ctx)->stash = NULL;
	(*ctx)->opened_fd = NULL;
	(*ctx)->exitcode = 0;
}

int minishell(int argc, char **argv, char **envp)
{
    char	*statement;
	t_node	*ast;
	t_ctx	*ctx;
	
	init_ctx(&ctx, envp);
	ast = NULL;
	char prompt[] = "\033[1;32mminishell$ \033[0m"; 

    if (argc == 2 || !envp) 
    {
        parse(argv[1], ctx);
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
        ast = parse(statement, ctx);
		if (!ast)
			continue ;
        	// execute(ast);
        free(statement);
    }
}

int	main(int argc, char **argv, char **envp)
{
	minishell(argc, argv, envp);

	// t_node *node;
	// pid_t	pid;
	// (void)pid;
	// (void)argc;
	// (void)argv;
	// (void)envp;

	// node = init_testcase_forward();
	// save_tree(node);
	// evaluate_node(node);

	// //start from process_group? group = init prompt
	// // while (1)
	// // {
	// // 	//get_prompt() / get_tree() //readline here

	// 	printf("exitcode: %d\n", node->ctx->exitcode);
	// // }

	return (EXIT_SUCCESS);
}
