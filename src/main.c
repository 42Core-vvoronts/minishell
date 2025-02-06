/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/06 12:46:23 by ipetrov          ###   ########.fr       */
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
		error(ctx, STRUCT_CTX, MALLOC_FAIL, true);
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
			error(ctx, STRUCT_CTX, MALLOC_FAIL, true);
		i++;
	}
	ctx->envp[i] = NULL;
	return (SUCCESS);
}

int	init_ctx(t_ctx **ctx, char **envp)
{
	*ctx = ft_calloc(1, sizeof(t_ctx));
	if (!*ctx)
		error(NULL, NONE, MALLOC_FAIL, true);
	(*ctx)->ttyname = ttyname(STDIN_FILENO);
	if (!(*ctx)->ttyname)
		error(ctx, STRUCT_CTX, MALLOC_FAIL, true);
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

void	parse(char *input)
{
	(void)input;
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
	(void)ctx;
	(void)node;

	init_ctx(&ctx, envp);
	node = init_testcase_forward(ctx);

	node->ctx->stash = malloc(sizeof(char *) * 3);
	node->ctx->stash[0] = "export";
	node->ctx->stash[1] = ft_strdup("VAR2=VAR232");
	node->ctx->stash[2] = NULL;

	run_export(node);

	// save_tree(node);
	// evaluate_node(node);
	// printf("Result VAR: %s\n", get_var(ctx, "PATH"));
	// printf("Result VAL: %s\n", get_val(ctx, "HOME"));

	// char *input;

	// while (1)
	// {
	// 	input = readline("prompt: ");
	// 	add_history(input);
	// 	rl_on_new_line(); //?????
	// 	parse(input);
	// 	init_ctx(&ctx, envp);
	// 	node = init_testcase_forward(ctx);
		// evaluate_node(node);
	// 	restore_std(node);
	// 	printf("exitcode: %d\n", node->ctx->exitcode);
	// }
	// 	allclean(node);
	// save_tree(node);

	// (void)input;

	// //start from process_group? group = init prompt
	// // while (1)
	// // {
	// // 	//get_prompt() / get_tree() //readline here

	// // }
	return (EXIT_SUCCESS);
}
