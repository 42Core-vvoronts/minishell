/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 07:59:30 by ipetrov           #+#    #+#             */
/*   Updated: 2025/03/02 01:55:52 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// setup_signal(SIGQUIT, SIG_IGN, &node);
// setup_signal(SIGINT, handle_sigint_prompt, &node);
//SIG_IGN
static	void	setup_prompt_signals(struct sigaction sa, void *ctx)
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

static	void	setup_binary_signals(struct sigaction sa, void *ctx)
{
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}

static	void	setup_running_signals(struct sigaction sa, void *ctx)
{
	sa.sa_handler = handle_running_signal;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGTERM, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
	sa.sa_handler = handle_running_sigpipe;
	if (sigaction(SIGPIPE, &sa, NULL) == ERROR)
		error(-1, ctx, (t_m){strerror(errno)});
}

static	void	setup_heredoc_signals(struct sigaction sa, void *ctx)
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

void	setup_signals(int mode, void *ctx)
{
	struct sigaction	sa;

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
