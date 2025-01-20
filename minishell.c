/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:34 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/20 11:14:40 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


int main(int argc, char **argv) 
{
    char *cmdline;
    // char prompt[] = "minishell$ ";
	char prompt[] = "\033[1;32mminishell$ \033[0m"; 

//     if (argc == 2) {
//         // If there's an argument, parse it directly
//         parsing(argv[1]);
//         return 0;
//     }

//     while (1) {
//         cmdline = readline(prompt);
//         if (!cmdline) {
//             ft_printf("\n");
//             exit(1);
//         }

//         // // Check for heredoc operator (<<) in the command line
//         // if (strstr(cmdline, "<<")) {
//         //     // Extract delimiter (text after <<)
//         //     char *delimiter = strtok(cmdline, " \t");
//         //     delimiter = strtok(NULL, " \t");  // Get the actual delimiter
//         //     if (delimiter) {
//         //         handle_heredoc(delimiter, &cmdline);  // Replace cmdline with heredoc content
//         //     }
//         // }

//         printf("cmdline after heredoc: %s\n", cmdline);

//         // Now parse the modified command line
//         parsing(cmdline);

//         free(cmdline);  // Free memory after usage
//     }
// }
    if (argc == 2) 
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
