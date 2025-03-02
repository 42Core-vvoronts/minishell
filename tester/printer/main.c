/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:59:51 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 12:21:52 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_name(t_type cmd)
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
		case ARGUMENT:
			return "ARGUMENT";
		case CONTENT:
			return "CONTENT";
		case FILENAME:
			return "FILENAME";
	}
	return "UNDEFINED";
}

static char *escape_special_chars(const char *str)
{
    size_t len = strlen(str);
    char *escaped = malloc(len * 2 + 1);  // Allocate space for escaped string
    if (!escaped) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '"' || str[i] == '\\' || str[i] == '\n') {
            escaped[j++] = '\\';  // Escape special characters
        }
        escaped[j++] = str[i];
    }
    escaped[j] = '\0';  // Null-terminate
    return escaped;
}

static void print_graphviz(t_node *node, FILE *stream)
{
    if (node == NULL)
		return;
	char *escaped_token = escape_special_chars(node->token);
	char *type_name = get_name(node->type);

	fprintf(stream, "    n%p [label=\"%s\n%s\"];\n", (void*)node, type_name, escaped_token);

    // Free the escaped token string
    free(escaped_token);

    // Process left and right children
    if (node->left) {
        fprintf(stream, "    n%p -> n%p;\n", (void*)node, (void*)node->left);
        print_graphviz(node->left, stream);
    }
	else
	{
		fprintf(stream, "    n%p -> n%p;\n", (void*)node, (void*)(node->token));
		fprintf(stream, "    n%p [label=\"%s\"];\n", (void*)(node->token), "(null)");
	}
    if (node->right) {
        fprintf(stream, "    n%p -> n%p;\n", (void*)node, (void*)node->right);
        print_graphviz(node->right, stream);
    }
	else
	{
		fprintf(stream, "    n%p -> n%p;\n", (void*)node, (void*)(node->token + 1));
		fprintf(stream, "    n%p [label=\"%s\"];\n", (void*)(node->token + 1), "(null)");
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
	printf("    graph [bgcolor=\"#212830\"];\n");
	printf("    node [shape=box, style=rounded, fontname=\"Helvetica\", color=\"#d1d7e0\", \
				fillcolor=\"#262c36\", fontcolor=\"#d1d7e0\", style=filled];\n");
	printf("    edge [color=\"#d1d7e0\"];\n");
    print_graphviz(node, stdout);
    printf("}\n");
	fflush(stdout);


	pid = fork();
	if (pid == 0)
	{
		char *args[] = {"dot", "-Tpng", "temp.dot", "-o", "result_tree.png", NULL};
		if (execvp(args[0], args) == -1)
			ft_putstr_fd("Install graphviz to get tree:\n	sudo apt upgrade && apt install graphviz\n", STDERR_FILENO);
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

void print_tokens(t_tok *token)
{
	while (token)
	{
		printf("%s: %s\n", get_name(token->type), token->lexeme);
		token = token->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*statement;
	t_ctx	*ctx;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		statement = readline("minishell$ ");
		if (!statement)
			return (1);
		ctx = ft_calloc(1, sizeof(t_ctx));
		save_tree(parse(statement, ctx));
	}
	return (EXIT_SUCCESS);
}
