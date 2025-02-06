/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/06 09:11:20 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static	void	update_envp(t_node *node, size_t len)
{
	size_t	i;
	char **result;

	i = 0;
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	while (i < len)
	{
		if ((node->ctx->envp)[i])
			result[i] = (node->ctx->envp)[i];
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
	size_t	len;
	char	**var;

	if (!node->ctx->envp || !node->ctx->stash)
		return ;
	i = 1;
	len = ft_parrlen(node->ctx->envp);
	while ((node->ctx->stash)[i])
	{
		var = get_var(node->ctx, (node->ctx->stash)[i]);
		if (var)
		{
			free(*var);
			*var = NULL;
			len--;
		}
		i++;
	}
	update_envp(node, len);
	node->ctx->exitcode = EXIT_SUCCESS;
}
