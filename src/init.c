/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:29:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 04:48:48 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(*ctx)->exitcode = EXIT_SUCCESS;
	init_envp(*ctx, envp);
	return (SUCCESS);
}
