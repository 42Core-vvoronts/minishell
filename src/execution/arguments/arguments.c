/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:19:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 13:11:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(char *arg, t_node *node)
{
	size_t	i;
	char **result;

	i = ft_parrlen(node->ctx->stash);
	result = ft_calloc(i + 2, sizeof(char *));
	if (!result)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	i = 0;
	while (node->ctx->stash && (node->ctx->stash)[i])
	{
		result[i] = (node->ctx->stash)[i];
		i++;
	}
	result[i] = arg;
	free(node->ctx->stash);
	node->ctx->stash = result;
}

char	*pop_arg(t_node *node)
{
	size_t	i;
	char **result;
	char *arg;

	i = ft_parrlen(node->ctx->stash);
	result = ft_calloc(i, sizeof(char *));
	if (!result)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	i = 0;
	while (node->ctx->stash && (node->ctx->stash)[i + 1])
	{
		result[i] = (node->ctx->stash)[i];
		i++;
	}
	arg = (node->ctx->stash)[i];
	free(node->ctx->stash);
	node->ctx->stash = result;
	return (arg);
}

void prepare_argv(t_node *node)
{
	size_t 	i;
	char **result;
	char **tmp;

	tmp = NULL;
	result = NULL;
	i = 0;
	while (node->ctx->stash && (node->ctx->stash)[i])
	{
		tmp = ft_split((node->ctx->stash)[i], ' ');
		if (!tmp)
		{
			ft_parrclean(result);
			error(node, STRUCT_NODE, MALLOC_FAIL, true);
		}
		result = ft_parrjoin(result, tmp);
		i++;
	}
	ft_parrclean(&(node->ctx->stash));
	node->ctx->stash = result;
}
