/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/07 03:41:52 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

//21474836490000000000
static	bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || i == 19)
			return (false);
		i++;
	}
	return (true);
}

static	void	put_exitcode(t_node *node)
{
	int	sts;
	sts = ft_atoi(node->ctx->stash[1], &node->ctx->exitcode, sizeof(int), 10);
	if (sts == FAIL)
		node->ctx->exitcode = 1;
}

void	run_exit(t_node *node)
{
	puterr("exit\n");
	if (node->ctx->stash[1])
	{
		if (is_eqlstr(node->ctx->stash[1], "--"))
		{
			// allclean(node);
			exit(EXIT_SUCCESS);
		}
		if (!is_numeric(node->ctx->stash[1]))
		{
			node->ctx->hint = ft_strdup(node->ctx->stash[1]);
			error(node, STRUCT_NODE, NON_NUMERIC_EXIT, true);
		}
		if (node->ctx->stash[2])
		{
			error(node, STRUCT_NODE, TOO_MANY_ARG_EXIT, false);
			return ;
		}
		put_exitcode(node);
	}
	// printf("%d\n", node->ctx->exitcode);
	exit(node->ctx->exitcode);
}
