/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/11 12:01:19 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

int	main(int argc, char **argv, char **envp)
{
	setup_signals(IS_PROMPT, NULL);
	prompt(argc, argv, envp);
	return (EXIT_SUCCESS);
}
