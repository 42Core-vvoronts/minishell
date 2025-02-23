/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 07:59:30 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 03:51:38 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _POSIX_C_SOURCE 200809L
#include "minishell.h"

static	void handle_signal(int signum)
{
	(void)signum;
	if (write(STDOUT_FILENO, "\n", 1) == ERROR)
		error(-1, NULL, (t_m){strerror(errno)});
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = signum;
}

static	void handle_running_signal(int signum)
{
	(void)signum;
	g_signal = signum;
}

static	void handle_heredoc_signal(int signum)
{
	handle_signal(signum);
	close(STDIN_FILENO);
}

// setup_signal(SIGQUIT, SIG_IGN, &node);
// setup_signal(SIGINT, handle_sigint_prompt, &node);
//SIG_IGN
static void setup_prompt_signals(struct sigaction sa, void *ctx)
{
	sa.sa_handler = handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}

static void setup_binary_signals(struct sigaction sa, void *ctx)
{
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}

static void setup_running_signals(struct sigaction sa, void *ctx)
{
	sa.sa_handler = handle_running_signal;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}

static void setup_heredoc_signals(struct sigaction sa, void *ctx)
{
	sa.sa_handler = handle_heredoc_signal;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}

void setup_signals(int mode, void *ctx)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (mode == IS_PROMPT)
		setup_prompt_signals(sa, ctx);
	else if (mode == IS_BINARY)
		setup_binary_signals(sa, ctx);
	else if (mode == IS_RUNNING)
		setup_running_signals(sa, ctx);
	else if (mode == IS_HEREDOC)
		setup_heredoc_signals(sa, ctx);
}
