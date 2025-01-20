/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:19:41 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/20 18:30:12 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void traverse_ast(t_ast *node, t_ctx *ctx);

int init_ctx(t_ctx **ctx)
{
	*ctx = ft_calloc(1, sizeof(t_ctx));
	if (!*ctx)
		return (FAIL);
	(*ctx)->ttyname = ttyname(STDIN_FILENO);
	return (SUCCESS);
}

int init_envp(t_ctx *ctx, char **envp)
{
	size_t	len;
	int		i;

	len = ft_parrlen(envp);
	ctx->envp = ft_calloc(len + 1, sizeof(char *));
	if (!ctx->envp)
		return (FAIL);
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
		{
			ft_parrclean(0, free, ctx->envp, NULL);
			return (FAIL);
		}
		i++;
	}
	ctx->envp[i] = NULL;
	return (SUCCESS);
}

int init(t_ctx **ctx, char **envp)
{
	if (init_ctx(ctx) == FAIL)
		return (FAIL);
	if (init_envp(*ctx, envp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx *ctx;
	t_ast *tree;

	if (init(&ctx, envp) == FAIL)
	{
		return (EXIT_FAILURE);
	}

	// tree = parsing("/bin/cat f1.txt | /bin/cat");
	tree = parsing("/bin/ls / | /bin/cat | /bin/cat");
	traverse_ast(tree, ctx);
	// run_pipeline(ctx, NULL);
	// run_cmd(ctx, cmd);

	wait(NULL);
	printf("\ntest STDOUT\n");
	char test[50];
	scanf("stdin: %s\n", test);
	return (EXIT_SUCCESS);
}
