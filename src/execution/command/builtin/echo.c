/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:50:25 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 03:02:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	void	process_option(char **stash, bool *newline, size_t *i)
{
	if (!stash[1])
		return ;
	if (is_eqlstr(stash[1], "-n"))
	{
		*i += 1;
		*newline = false;
		return ;
	}
}
void	run_echo(t_node *node)
{
	size_t	i;
	bool	newline;

	i = 0;
	newline = true;
	process_option(node->ctx->stash, &newline, &i);
	while ((node->ctx->stash)[++i])
	{
		putout(node->ctx->stash[i]);
		if (node->ctx->stash[i + 1])
			putout(" ");
	}
	if (newline)
		putout("\n");
	node->ctx->exitcode = EXIT_SUCCESS;
}
