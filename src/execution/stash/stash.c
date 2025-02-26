/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:19:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/26 04:14:38 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add argument to end of stash
//it doesnt duplicate arg, it attachs it
void	add_stash(char *arg, t_node *node)
{
	size_t	i;
	char **result;

	i = ft_parrlen(node->ctx->stash);
	result = ft_calloc(i + 2, sizeof(char *));
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno)});
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

//get argument on end of stash and remove it from stash
char	*pop_stash(t_node *node)
{
	size_t	i;
	char **result;
	char *arg;

	if (!node->ctx->stash)
		return (NULL);
	i = ft_parrlen(node->ctx->stash);
	result = ft_calloc(i + 1, sizeof(char *));
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno)});
	i = 0;
	while ((node->ctx->stash)[i + 1])
	{
		result[i] = (node->ctx->stash)[i];
		i++;
	}
	arg = (node->ctx->stash)[i];
	free(node->ctx->stash);
	node->ctx->stash = result;
	return (arg);
}

