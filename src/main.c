/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 04:15:31 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *init_testcase_forward(t_ctx *ctx);
void save_tree(t_node *node);

static	int	init_envp(t_ctx *ctx, char **envp)
{
	size_t	len;
	size_t	i;

	len = ft_parrlen(envp);
	ctx->envp = ft_calloc(len + 1, sizeof(char *));
	if (!ctx->envp)
		error(ctx, STRUCT_CTX, MALLOC);
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
			error(ctx, STRUCT_CTX, MALLOC);
		i++;
	}
	ctx->envp[i] = NULL;
	return (SUCCESS);
}

int	init_ctx(t_ctx **ctx, char **envp)
{
	*ctx = ft_calloc(1, sizeof(t_ctx));
	if (!*ctx)
		error(NULL, NONE, MALLOC);
	(*ctx)->ttyname = ttyname(STDIN_FILENO);
	if (!(*ctx)->ttyname)
		error(ctx, STRUCT_CTX, MALLOC);
	init_envp(*ctx, envp);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*node;
	t_ctx	*ctx;
	pid_t	pid;

	(void)pid;
	(void)argc;
	(void)argv;
	(void)envp;

	init_ctx(&ctx, envp);
	node = init_testcase_forward(ctx);
	save_tree(node);
	evaluate_node(node);

	//start from process_group? group = init prompt
	// while (1)
	// {
	// 	//get_prompt() / get_tree() //readline here

		printf("exitcode: %d\n", node->ctx->exitcode);
	// }

	return (EXIT_SUCCESS);
}
