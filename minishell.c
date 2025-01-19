/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:34 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/19 10:53:45 by vvoronts         ###   ########.fr       */
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
		printf("cmdline: %s\n", cmdline);
        
        // history(cmdline);   
        parsing(cmdline);
        // execution();
        free(cmdline);
    }
}
