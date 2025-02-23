/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:19:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/11 06:31:54 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add argument to end of stash
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

//get argument on top of stash
char	*pop_stash(t_node *node)
{
	size_t	i;
	char **result;
	char *arg;

	i = ft_parrlen(node->ctx->stash);
	result = ft_calloc(i, sizeof(char *));
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno)});
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

//split by space?
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
			error(-1, node->ctx, (t_m){strerror(errno)});
		}
		result = ft_parrjoin(result, tmp);
		i++;
	}
	ft_parrclean(&(node->ctx->stash));
	node->ctx->stash = result;
}
