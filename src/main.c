/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 16:50:22 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *init_testcase_forward(void);
void save_tree(t_node *node);

// void handle_heredoc(char *delimiter, char **statement) {
//     char *line;
//     char *content = malloc(1);
//     content[0] = '\0';

//     // Read input until delimiter is encountered
//     while (1) {
//         line = readline("heredoc> ");
//         if (line == NULL || strcmp(line, delimiter) == 0) {
//             break;
//         }
//         // Append the input to the content
//         content = realloc(content, strlen(content) + strlen(line) + 1);
//         strcat(content, line);
//         strcat(content, "\n");
//         free(line);
//     }

//     // Replace <<delimiter>> with the heredoc content
//     *statement = content;  // Replace statement with heredoc content
// }


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
