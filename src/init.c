/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:29:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/25 05:36:34 by ipetrov          ###   ########.fr       */
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
	(*ctx)->fdin = dup(STDIN_FILENO);
	(*ctx)->fdout = dup(STDOUT_FILENO);
	(*ctx)->exitcode = EXIT_SUCCESS;
	(*ctx)->panic = false;
	init_envp(*ctx, envp);
	return (SUCCESS);
}

// void	restore_std(t_node *node)
// {
// 	int	fd;

// 	fd = eopen(node->ctx->ttyname, O_RDWR, 0777, node);
// 	edup2(fd, STDIN_FILENO, node);
// 	edup2(fd, STDOUT_FILENO, node);
// 	close(fd);
// }

/**
 * @brief Init a new tree node
 *
 * @param type The type of the token
 * @param token The token
 * @param left The left node
 * @param right The right node

 * @return t_node*
 *
 */
t_node	*init_node(t_type type, char *lexeme, t_node *left, t_node *right, t_ctx *ctx)
{
    t_node *node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		error(-1, NULL, (t_m){strerror(errno), NULL});
    node->ctx = ctx;
    node->type = type;
    node->token = lexeme;
    node->left = left;
    node->right = right;
    return node;
}

/**
 * @brief Init a new token node
 *
 * @param start The start character of the lexeme
 * @param len The length of the lexeme
 * @param ctx The context

 * @return pointer to the new node
 *
 */
t_tok	*init_token(char *start, int len, t_ctx *ctx)
{
	t_tok	*token;

	token = ft_calloc(1, sizeof(t_tok));
	if (!token)
		error(-1, ctx, (t_m){strerror(errno), NULL});
	token->lexeme = ft_strndup(start, len);
	if (!token->lexeme)
		error(-1, ctx, (t_m){strerror(errno), NULL});
	token->type = typify_token(token->lexeme);
	token->next = NULL;
	return token;
}
