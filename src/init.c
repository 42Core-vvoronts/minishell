/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:29:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 10:23:20 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	init_envp(t_ctx *ctx, char **envp)
{
	size_t	len;
	size_t	i;

	len = ft_parrlen(envp);
	ctx->envp = ft_calloc(len + 1, sizeof(char *));
	if (!ctx->envp)
		error(-1, NULL, (t_m){strerror(errno), NULL});
	i = 0;
	if (envp[i] == NULL)
	{
		ctx->envp[i] = NULL;
		return (SUCCESS);
	}
	while (i < len)
	{
		ctx->envp[i] = ft_strdup(envp[i]);
		if (!ctx->envp[i])
			error(-1, ctx, (t_m){strerror(errno), NULL});
		i++;
	}
	ctx->envp[i] = NULL;
	return (SUCCESS);
}

int	init_ctx(t_ctx **ctx, char **envp)
{
	*ctx = ft_calloc(1, sizeof(t_ctx));
	if (!*ctx)
		error(-1, NULL, (t_m){strerror(errno), NULL});
	(*ctx)->ttyname = ttyname(STDIN_FILENO);
	// if (!(*ctx)->ttyname)
	// 	error(ctx, STRUCT_CTX, MALLOC_FAIL, true);
	init_envp(*ctx, envp);
	return (SUCCESS);
}

void	restore_std(t_node *node)
{
	int	fd;

	fd = eopen(node->ctx->ttyname, O_RDWR, 0777, node);
	edup2(fd, STDIN_FILENO, node);
	edup2(fd, STDOUT_FILENO, node);
	close(fd);
}
