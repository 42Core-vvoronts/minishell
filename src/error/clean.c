/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:43:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 18:59:34 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_tree(t_node *node)
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

	if (mode == 1)
	{
		ft_parrclean(&(node->ctx->envp));
		ft_parrclean(&(node->ctx->stash));
	}
	ctx = node->ctx;
	clean_tree(node->ctx->head);
	exitcode = ctx->exitcode;
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
