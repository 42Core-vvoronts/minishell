/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:59:51 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 18:30:48 by vvoronts         ###   ########.fr       */
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
		char *args[] = {"dot", "-Tpng", "temp.dot", "-o", "result_tree.png", NULL};
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

const char *get_name(t_type cmd) 
{
	switch (cmd) 
	{
		case AND:
			return "AND";
		case OR:
			return "OR";
		case GROUP:
			return "GROUP";
		case PIPE:
			return "PIPE";
		case REDIR_IN:
			return "REDIR_IN";
		case REDIR_OUT:
			return "REDIR_OUT";
		case REDIR_APPEND:
			return "REDIR_APPEND";
		case REDIR_HEREDOC:
			return "REDIR_HEREDOC";
		case WORD_ZERO_QUOTES:
			return "WORD_ZERO_QUOTES";
		case WORD_SINGLE_QUOTES:
			return "WORD_SINGLE_QUOTES";
		case WORD_DOUBLE_QUOTES:
			return "WORD_DOUBLE_QUOTES";
	}
	return "UNDEFINED";
}


void print_tokens(t_tok *token)
{
	while (token)
	{
		printf("%s: %s\n", get_name(token->type), token->lexeme);
		token = token->next;
	}
}
