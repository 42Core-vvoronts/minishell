/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:43:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 06:33:53 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tree(t_node *node)
{
	if (node == NULL)
		return ;
	clean_tree(node->left);
	clean_tree(node->right);
	free(node);
}

int	allclean(t_node *node, int mode)
{
	t_ctx	*ctx;
	int		exitcode;

	if (mode == FULL)
	{
		if (node->ctx->envp)
			ft_parrclean(&(node->ctx->envp));
		if (node->ctx->stash)
			ft_parrclean(&(node->ctx->stash));
	}
	ctx = node->ctx;
	exitcode = ctx->exitcode;
	if (node->ctx->head)
		clean_tree(node->ctx->head);
	close(ctx->fdin);
	close(ctx->fdout);
	free(ctx);
	return (exitcode);
}

void	clean_tokens(t_tok **tokens)
{
	t_tok	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->lexeme);
		free(tmp);
	}
}
