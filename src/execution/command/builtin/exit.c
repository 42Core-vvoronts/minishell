/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 09:56:00 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//21474836490000000000
static	bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static	int	evaluate_exitcode(t_node *node)
{
	int	sts;

	sts = ft_atoi(node->ctx->stash[1], &node->ctx->exitcode, sizeof(int), 10);
	if (sts == FAIL)
		node->ctx->exitcode = 1;
	return (node->ctx->exitcode);
}

void	run_exit(t_node *node)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (node->ctx->stash && node->ctx->stash[1])
	{
		node->ctx->exitcode = evaluate_exitcode(node);
		if (node->ctx->stash[2])
		{
			error(1, node->ctx, (t_m){EXIT, TOO_MANY_ARG});
			return ;
		}
		else if (is_eqlstr(node->ctx->stash[1], "--"))
			node->ctx->exitcode = EXIT_SUCCESS;
		else if (!is_numeric(node->ctx->stash[1]))
			error(2, node->ctx, (t_m){EXIT, node->ctx->stash[1], EXIT_NON_NUM});
	}
	exit(allclean(node, FULL));
}
