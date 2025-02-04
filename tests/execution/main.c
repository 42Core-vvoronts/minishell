/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:19:41 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/04 08:45:36 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	evaluate_node(t_node *node);

int	open_pipe(t_pipe *p)
{
	int	fd[2];

	if (pipe(fd) == ERROR)
	{
		return (1);
		// return (error(PIPE, NULL));
	}
	p->read = fd[0];
	p->write = fd[1];
	return (SUCCESS);
}

int	close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
	return (SUCCESS);
}

t_node *init_testcase_forward(void)
{
	t_ctx *ctx;
	t_node *node;

	ctx = malloc(sizeof(t_ctx));
	ctx->stash = malloc(sizeof(char *));
	*(ctx->stash) = NULL;
	// ls / < f1 | cat | grep a
	(node) = malloc(sizeof(t_node));
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
	(node->left->left)->token = "f1";
	(node->left->left)->left = malloc(sizeof(t_node));

	(node->left)->right = malloc(sizeof(t_node));
	(node->left->right)->ctx = ctx;
	(node->left->right)->type = WORD_ZERO_QUOTES;
	(node->left->right)->token = "/gin/ls";
	(node->left->right)->left = NULL;

	(node->left->right)->right =  malloc(sizeof(t_node));
	(node->left->right->right)->ctx = ctx;
	(node->left->right->right)->type = WORD_ZERO_QUOTES;
	(node->left->right->right)->token = "/";

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

	return (node);
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

void print_graphviz(t_node *node, FILE *stream)
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

void	add_arg(char *arg, char * **stash)
{
	size_t	i;
	char **result;

	i = ft_parrlen(*stash);
	result = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*stash)[i])
	{
		result[i] = (*stash)[i];
		i++;
	}
	result[i] = arg;
	i++;
	result[i] = NULL;
	free(*stash);
	*stash = result;
}

char	*pop_arg(char * **stash)
{
	size_t	i;
	char **result;
	char *arg;

	i = ft_parrlen(*stash);
	result = malloc(sizeof(char *) * i);
	i = 0;
	while ((*stash)[i + 1])
	{
		result[i] = (*stash)[i];
		i++;
	}
	result[i] = NULL;
	arg = (*stash)[i];
	free(*stash);
	*stash = result;
	return (arg);
}

char **get_argv(char * **args)
{
	size_t 	i;
	char **result;
	char *tmp;

	tmp = "";
	i = 0;
	while ((*args)[i])
	{
		tmp = ft_strjoin(tmp, (*args)[i]);
		i++;
	}
	result = ft_split(tmp, ' ');
	free(*args);
	*args = NULL;
	return (result);
}
static int	get_exitcode(pid_t pid)
{
	int		status;
	pid_t	child;
	int		exitcode;

	child = 0;
	exitcode = 1;
	while (child != -1)
	{
		child = wait(&status);
		if (child == pid)
		{
			if (WIFEXITED(status))
			{
				exitcode = WEXITSTATUS(status);
			}
		}
	}
	return (exitcode);
}


void run_cmd(t_node *node)
{
	char	*pathname;
	char	**argv;

	argv = get_argv(&(node->ctx->stash));
	execve(argv[0], argv, node->ctx->envp);
	// and clean collected fd
	exit(1);
}

void	process_pipe(t_node *node)
{
	t_pipe	p;
	pid_t	pid;

	open_pipe(&p);
	pid = fork(); //check for fail
	if (pid == 0)
	{
		// dup2(p.write, STDOUT_FILENO);
		close_pipe(&p);
		evaluate_node(node->left);
		run_cmd(node); // execve() here all what i have in a stash
	}
	dup2(p.read, STDIN_FILENO);
	close_pipe(&p);
	if (node->right->type != PIPE)
	{
		pid = fork();
		if (pid == 0)
		{
			evaluate_node(node->right);
			run_cmd(node);
			// execeve() here and in init fork of not NULL;
			// or fork() and then exit(wait())
		}
		else if (pid > 0)
		{
			// fork();??
			node->ctx->exitcode = get_exitcode(pid); //waitpid()?? skips all other pids?
			//collect all other children exitcode here as well
		}
		return ;
	}
	evaluate_node(node->right);
	return ;
}

// void	process_pipe_reverse(t_node *node)
// {
// 	t_pipe	p;
// 	pid_t	pid;

// 	open_pipe(&p);
// 	if (node->left->type == PIPE)
// 	{
// 		dup2(p.write, STDOUT_FILENO);
// 		evaluate_node(node->left);
// 	}
// 	else
// 	{

// 	}
// }

void	process_redir_in(t_node *node)
{
	int	fd;
	char	*pathname;

	evaluate_node(node->left);
	pathname = pop_arg(&(node->ctx->stash));
	//ft_split result of pop arg
	fd = open(pathname, O_RDONLY); //change to get last arg from args
	if (fd == ERROR)
	{
		free(pathname);
		//clean all previos opened fd, exitcode (1)
		//init prompt always fork()
		//cleanfd()
		//clean whole ctx and args
		node->ctx->exitcode = REDIR_FAIL; //make REDIR_FAIL = 1 macro
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	evaluate_node(node->right);
}

void	process_word_zero_quotes(t_node *node)
{
	//expand $var and expand *
	add_arg(ft_strdup(node->token), &(node->ctx->stash));
}

void	process_word_single_quotes(t_node *node)
{
	//expand $var and expand *
	add_arg(ft_strdup(node->token), &(node->ctx->stash));
}

void	process_word_double_quotes(t_node *node)
{
	//expand $var and expand *
	add_arg(ft_strdup(node->token), &(node->ctx->stash));
}

void	process_group(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		evaluate_node(node->right);
		return ;
	}
	else if (pid > 0)
	{
		node->ctx->exitcode = get_exitcode(pid); //last_child
		return ;
	}
}

void	process_and(t_node	*node)
{
	int	exitcode;

	if (node->left->type == AND || node->left->type == OR)
	{
		evaluate_node(node->left);
	}
	evaluate_node(node->left);

	if (node->ctx->exitcode == EXIT_SUCCESS)
	{
		evaluate_node(node->right);
	}
}

void	process_or(t_node	*node)
{
	int	exitcode;

	if (node->left->type == AND || node->left->type == OR)
	{
		evaluate_node(node->left);
	}
	evaluate_node(node->left);

	if (node->ctx->exitcode != EXIT_SUCCESS)
	{
		evaluate_node(node->right);
	}
}

void	evaluate_node(t_node *node)
{
	if (node == NULL || node->ctx->exitcode != EXIT_SUCCESS)
	{
		return ;
	}
	if (node->type == PIPE)
	{
		process_pipe(node);
	}
	else if (node->type == REDIR_IN)
	{
		process_redir_in(node);
	}
	else if (node->type == REDIR_OUT)
	{

	}
	else if (node->type == REDIR_APPEND)
	{

	}
	else if (node->type == REDIR_HEREDOC_NOQUOTES)
	{

	}
	else if (node->type == REDIR_HEREDOC_QUOTES)
	{

	}
	else if (node->type == WORD_ZERO_QUOTES)
	{
		process_word_zero_quotes(node);
	}
	else if (node->type == WORD_SINGLE_QUOTES)
	{
		process_word_single_quotes(node);
	}
	else if (node->type == WORD_DOUBLE_QUOTES)
	{
		process_word_double_quotes(node);
	}
	else if (node->type == GROUP)
	{
		process_group(node);
	}
	else if (node->type == AND)
	{
		process_and(node);
	}
	else if (node->type == OR)
	{
		process_or(node);
	}
	else
	{
		return ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_node *node;
	pid_t	pid;

	node = init_testcase_forward();
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
