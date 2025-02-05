/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:59:51 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:40:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void print_graphviz(t_node *node, FILE *stream)
{
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
	fflush(stdout);


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
		fd = open(ttyname(STDIN_FILENO), O_RDWR, 777);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
