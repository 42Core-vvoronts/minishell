/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:19:41 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/03 09:37:33 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void traverse_ast(t_ast *node, t_ctx *ctx);

// int init_ctx(t_ctx **ctx)
// {
// 	*ctx = ft_calloc(1, sizeof(t_ctx));
// 	if (!*ctx)
// 		return (FAIL);
// 	(*ctx)->ttyname = ttyname(STDIN_FILENO);
// 	return (SUCCESS);
// }

// int init_envp(t_ctx *ctx, char **envp)
// {
// 	size_t	len;
// 	int		i;

// 	len = ft_parrlen(envp);
// 	ctx->envp = ft_calloc(len + 1, sizeof(char *));
// 	if (!ctx->envp)
// 		return (FAIL);
// 	i = 0;
// 	if (envp[i] == NULL)
// 	{
// 		ctx->envp[i] = NULL;
// 		return (SUCCESS);
// 	}
// 	while (i < len)
// 	{
// 		ctx->envp[i] = ft_strdup(envp[i]);
// 		if (!ctx->envp[i])
// 		{
// 			ft_parrclean(0, free, ctx->envp, NULL);
// 			return (FAIL);
// 		}
// 		i++;
// 	}
// 	ctx->envp[i] = NULL;
// 	return (SUCCESS);
// }

// int init(t_ctx **ctx, char **envp)
// {
// 	if (init_ctx(ctx) == FAIL)
// 		return (FAIL);
// 	if (init_envp(*ctx, envp) == FAIL)
// 		return (FAIL);
// 	return (SUCCESS);
// }

// //make waitpid handler separate
// int get_exitcode(pid_t pid)
// {
// 	int		status;
// 	pid_t	child;
// 	int		exitcode;

// 	child = 0;
// 	exitcode = -1;
// 	while (child != -1)
// 	{
// 		child = wait(&status);
// 		if (child == pid)
// 		{
// 			if (WIFEXITED(status))
// 			{
// 				exitcode = WEXITSTATUS(status);
// 			}
// 		}
// 	}
// 	return (exitcode);
// }

t_node *init_testcase(void)
{
	t_node *node;

	// ls / < f1 | cat | grep a
	(node) = malloc(sizeof(t_node));
	(node->type) = PIPE;
	(node->token) = "|";

	(node->left) = malloc(sizeof(t_node));
	(node->left)->type = PIPE;
	(node->left)->token = "|";
	(node->left)->left = malloc(sizeof(t_node));

	(node->left->left)->type = REDIR_IN;
	(node->left->left)->token = "<";
	(node->left->left)->left = malloc(sizeof(t_node));

	(node->left->left->left)->type = WORD_ZERO_QUOTES;
	(node->left->left->left)->token = "f1";
	(node->left->left->left)->left = NULL;
	(node->left->left->left)->right = NULL;

	(node->left->left)->right = malloc(sizeof(t_node));

	(node->left->left->right)->type = WORD_ZERO_QUOTES;
	(node->left->left->right)->token = "ls";
	(node->left->left->right)->left = NULL;
	(node->left->left->right)->right = malloc(sizeof(t_node));

	(node->left->left->right->right)->type = WORD_ZERO_QUOTES;
	(node->left->left->right->right)->token = "/";
	(node->left->left->right->right)->left = NULL;
	(node->left->left->right->right)->right = NULL;

	(node->left)->right = malloc(sizeof(t_node));

	(node->left->right)->type = WORD_ZERO_QUOTES;
	(node->left->right)->token = "cat";
	(node->left->right)->left = NULL;
	(node->left->right)->right = NULL;

	(node->right) = malloc(sizeof(t_node));
	(node->right)->type = WORD_ZERO_QUOTES;
	(node->right)->token = "grep";
	(node->right)->left = NULL;
	(node->right)->right = malloc(sizeof(t_node));

	(node->right->right)->type = WORD_ZERO_QUOTES;
	(node->right->right)->token = "a";
	(node->right->right)->left = NULL;
	(node->right->right)->right = NULL;

	return (node);
}


void print_graphviz(t_node *node, FILE *stream) {
    if (node == NULL) return;

    // Print current node
    fprintf(stream, "    n%p [label=\"%s\"];\n",
           (void*)node, node->token);

    // Process left child
    if (node->left) {
        fprintf(stream, "    n%p -> n%p;\n",
               (void*)node, (void*)node->left);
        print_graphviz(node->left, stream);
    }

    // Process right child
    if (node->right) {
        fprintf(stream, "    n%p -> n%p;\n",
               (void*)node, (void*)node->right);
        print_graphviz(node->right, stream);
    }
}

void save_tree(t_node *node)
{
	int 	fd;
	pid_t	pid;

	fd = open("temp.dot", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);

    printf("digraph G {\n");
    printf("    node [shape=box, style=rounded, fontname=\"Helvetica\"];\n");
    print_graphviz(node, stdout);
    printf("}\n");

	pid = fork();
	if (pid == 0)
	{
		char *args[] = {"dot", "-Tpng", "temp.dot", "-o", "tree.png", NULL};
		if (execvp(args[0], args) == -1)
			perror("execvp failed");
		exit(0);
	}
	else if (pid > 0)
	{
		wait(NULL);
		unlink("temp.dot");
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx *ctx;
	t_node *node;

	node = init_testcase();
	save_tree(node);

	return (EXIT_SUCCESS);
}
