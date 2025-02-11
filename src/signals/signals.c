/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 07:59:30 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/11 12:59:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _POSIX_C_SOURCE 200809L
#include "minishell.h"

static	void handle_signal(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		if (write(STDOUT_FILENO, "\n", 1) == ERROR)
			error(-1, NULL, (t_m){strerror(errno)});
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// g_signal = 128 + signum;
	}
}

// setup_signal(SIGQUIT, SIG_IGN, &node);
// setup_signal(SIGINT, handle_sigint_prompt, &node);
//SIG_IGN
void setup_signals(int mode, void *ctx)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	if (sigemptyset(&sa.sa_mask) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (mode == IS_PROMPT)
	{
		sa.sa_handler = handle_signal;
		if (sigaction(SIGINT, &sa, NULL) == ERROR)
			error(-1, ctx, (t_m){strerror(errno)});
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
			error(-1, ctx, (t_m){strerror(errno)});
		if (sigaction(SIGTERM, &sa, NULL) == ERROR)
			error(-1, ctx, (t_m){strerror(errno)});
		return ;
	}
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}
