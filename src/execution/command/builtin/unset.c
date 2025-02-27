/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/26 06:01:02 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	update_envp(t_node *node, size_t len)
{
	size_t	i;
	size_t	j;
	char **result;

	i = 0;
	j = 0;
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno)});
	while (node->ctx->envp[i])
	{
		if ((node->ctx->envp)[i][0] != 4)
		{
			result[j] = (node->ctx->envp)[i];
			j++;
		}
		else
			free((node->ctx->envp)[i]);
		i++;
	}
	free(node->ctx->envp);
	node->ctx->envp = result;
}

void	run_unset(t_node *node)
{
	size_t	i;
	size_t	j;
	size_t	len;

	node->ctx->exitcode = EXIT_SUCCESS;
	if (!node->ctx->envp || !node->ctx->stash)
		return ;
	i = 1;
	len = ft_parrlen(node->ctx->envp);
	while ((node->ctx->stash)[i])
	{
		j = -1;
		while (node->ctx->envp[++j])
		{
			if (is_eqlvar(node->ctx->envp[j], node->ctx->stash[i]))
			{
				node->ctx->envp[j][0] = 4;
				len--;
				break ;
			}
		}
		i++;
	}
	update_envp(node, len);
}
