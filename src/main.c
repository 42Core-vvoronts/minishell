/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 11:38:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *init_testcase_forward(void);
void save_tree(t_node *node);

// void handle_heredoc(char *delimiter, char **cmdline) {
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
//     *cmdline = content;  // Replace cmdline with heredoc content
// }


int minishell(int argc, char **argv, char **envp)
{
    char *cmdline;
    // char prompt[] = "minishell$ ";
	char prompt[] = "\033[1;32mminishell$ \033[0m"; 

    if (argc == 2 || !envp) 
    {
        parsing(argv[1]);
        // execution();
        return 0;
    }

    while (true) 
    {
        cmdline = readline(prompt);
        if (!cmdline) 
        {
            ft_printf("\n");
            exit(1); 
		}
		// printf("cmdline: %s\n", cmdline);
        
        // history(cmdline);   
        parsing(cmdline);
        // execution();
        free(cmdline);
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
