/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 07:59:30 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/28 03:38:38 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	// if (write(STDOUT_FILENO, "\n", 1) == ERROR)
	// 	error(-1, NULL, (t_m){strerror(errno)});
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = signum;
}

void	handle_running_signal(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		if (write(STDOUT_FILENO, "\n", 1) == ERROR)
			error(-1, NULL, (t_m){strerror(errno)});
	}
	else if (g_signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_heredoc_signal(int signum)
{
	if (write(STDOUT_FILENO, "\n", 1) == ERROR)
		error(-1, NULL, (t_m){strerror(errno)});
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal = signum;
	close(STDIN_FILENO);
}
