/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testcases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:04:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 08:35:40 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *init_testcase_forward(t_ctx *ctx)
{
	// t_ctx *ctx;
	t_node *node;
	t_node *node_m1;

	// ctx = malloc(sizeof(t_ctx));
	// ctx->stash = malloc(sizeof(char *));
	// *(ctx->stash) = NULL;

	(node_m1) = malloc(sizeof(t_node));
	(node_m1)->ctx = ctx;
	(node_m1)->type = AND;
	(node_m1)->token = "&&";

	(node_m1)->right = malloc(sizeof(t_node));
	(node_m1->right)->ctx = ctx;
	(node_m1->right)->type = WORD_ZERO_QUOTES;
	(node_m1->right)->token = "ls";
	(node_m1->right)->right = NULL;
	(node_m1->right)->left = NULL;


	// ls / < f1 | cat | grep a
	(node) = malloc(sizeof(t_node));
	(node_m1)->left = node;
	(node->ctx) = ctx;
	(node->type) = PIPE;
	(node->token) = "|";

	(node->left) = malloc(sizeof(t_node));
	(node->left)->ctx = ctx;
	(node->left)->type = REDIR_IN;
	(node->left)->token = "<";

	(node->left)->left = malloc(sizeof(t_node));
	(node->left->left)->ctx = ctx;
	(node->left->left)->type = WORD_ZERO_QUOTES;
	(node->left->left)->token = "./tests/f1";
	(node->left->left)->left = malloc(sizeof(t_node));

	(node->left)->right = malloc(sizeof(t_node));
	(node->left->right)->ctx = ctx;
	(node->left->right)->type = WORD_ZERO_QUOTES;
	(node->left->right)->token = "/bin/cat";
	(node->left->right)->left = NULL;

	(node->left->right)->right =  malloc(sizeof(t_node));
	(node->left->right->right)->ctx = ctx;
	(node->left->right->right)->type = WORD_ZERO_QUOTES;
	(node->left->right->right)->token = "/";


	(node->left->right)->right = NULL;


	(node->right) = malloc(sizeof(t_node));
	(node->right)->ctx = ctx;
	(node->right)->type = PIPE;
	(node->right)->token = "|";

	(node->right)->left = malloc(sizeof(t_node));
	(node->right->left)->ctx = ctx;
	(node->right->left)->type = WORD_ZERO_QUOTES;
	(node->right->left)->token = "/bin/cat";

	(node->right)->right = malloc(sizeof(t_node));
	(node->right->right)->ctx = ctx;
	(node->right->right)->type = WORD_ZERO_QUOTES;
	(node->right->right)->token = "/bin/grep";

	(node->right->right)->right = malloc(sizeof(t_node));
	(node->right->right->right)->ctx = ctx;
	(node->right->right->right)->type = WORD_ZERO_QUOTES;
	(node->right->right->right)->token = "a";
	(node->right->right->right)->right = NULL;

	return (node_m1);
}

t_node *init_testcase_reverse(void)
{
	t_ctx *ctx;
	t_node *node;

	ctx = malloc(sizeof(t_ctx));
	ctx->stash = malloc(sizeof(char *) * 2);
	// ls / < f1 | cat | grep a
	(node) = malloc(sizeof(t_node));
	(node->ctx) = ctx;
	(node->type) = PIPE;
	(node->token) = "|";

	(node->left) = malloc(sizeof(t_node));
	(node->left)->ctx = ctx;
	(node->left)->type = PIPE;
	(node->left)->token = "|";
	(node->left)->left = malloc(sizeof(t_node));

	(node->left->left)->ctx = ctx;
	(node->left->left)->type = REDIR_IN;
	(node->left->left)->token = "<";
	(node->left->left)->left = malloc(sizeof(t_node));

	(node->left->left->left)->ctx = ctx;
	(node->left->left->left)->type = WORD_ZERO_QUOTES;
	(node->left->left->left)->token = "f1";
	(node->left->left->left)->left = NULL;
	(node->left->left->left)->right = NULL;

	(node->left->left)->right = malloc(sizeof(t_node));

	(node->left->left->right)->ctx = ctx;
	(node->left->left->right)->type = WORD_ZERO_QUOTES;
	(node->left->left->right)->token = "/bin/ls";
	(node->left->left->right)->left = NULL;
	(node->left->left->right)->right = malloc(sizeof(t_node));

	(node->left->left->right->right)->ctx = ctx;
	(node->left->left->right->right)->type = WORD_ZERO_QUOTES;
	(node->left->left->right->right)->token = "/";
	(node->left->left->right->right)->left = NULL;
	(node->left->left->right->right)->right = NULL;

	(node->left)->right = malloc(sizeof(t_node));

	(node->left->right)->ctx = ctx;
	(node->left->right)->type = WORD_ZERO_QUOTES;
	(node->left->right)->token = "/bin/cat";
	(node->left->right)->left = NULL;
	(node->left->right)->right = NULL;

	(node->right) = malloc(sizeof(t_node));
	(node->right)->ctx = ctx;
	(node->right)->type = WORD_ZERO_QUOTES;
	(node->right)->token = "/bin/grep";
	(node->right)->left = NULL;
	(node->right)->right = malloc(sizeof(t_node));

	(node->right->right)->ctx = ctx;
	(node->right->right)->type = WORD_ZERO_QUOTES;
	(node->right->right)->token = "a";
	(node->right->right)->left = NULL;
	(node->right->right)->right = NULL;

	return (node);
}
