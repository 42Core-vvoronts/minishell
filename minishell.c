/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:34 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/13 18:31:36 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv) 
{
    char *cmdline;
    char prompt[] = "minishell$ ";

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
        
        // history(cmdline);   
        parsing(cmdline);
        // execution();
        free(cmdline);
    }
}


// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		printf("Usage: ./minishel \"expression\"\n");
// 		return 1;
// 	}
// 	parsing(argv[1]);
// 	execution();
	
// 	return 0;
// }

// int main(int argc, char **argv) {
//     char cmdline[1024]; // buffer for fgets
// 	char prompt[] = "minishel$ "; // command line prompt

//     while (1) {
//         printf("%s", prompt);

//         if ((fgets(cmdline, 1024, stdin) == NULL) && ferror(stdin)) {
//             error("fgets error");
//         }

//         if (feof(stdin)) {
//             printf("\n");
//             exit(0);
//         }

//         // remove trailing newline
//         cmdline[strlen(cmdline) - 1] = '\0';

//         // evaluate command line
//         eval(cmdline);
//     }
// }