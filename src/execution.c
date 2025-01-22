/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:01:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/22 11:30:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **add_arg(char **old, char *word)
{
	size_t len;
	char **new;
	size_t i;

	len = ft_parrlen(old);
	new = malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	new[i] = word;
	i++;
	new[i] = NULL;
	return (new);
}

void open_pipe(t_pipe *p)
{
	int fd[2];

	pipe(fd); //mb here handle errors??? //check error
	p->read = fd[0];
	p->write = fd[1];
}

//change to close_pipe()
void close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
}

void	process_before_left(t_ast *node, t_ctx *ctx, void **param)
{
	if (node->type == PIPE) // handle_pipe_before_left();/pre,in,post
	{
		t_pipe *p;

		*param = malloc(sizeof(t_pipe));
		p = *param;
		open_pipe(p);

		//change stdout
		dup2(p->write, STDOUT_FILENO);
	}
	else if (node->type == WORD)
	{
		ctx->argv = add_arg(ctx->argv, node->token);
	}
	else if (node->type == REDIR_OUT)
	{
		int fd;
		fd = open(node->right->token, O_WRONLY | O_CREAT, 0777); //check by access here?? before open
		//expand here as well
		dup2(fd, STDOUT_FILENO);
		node->right = node->right->right;
	}
	else if (node->type == REDIR_IN)
	{
		int fd;
		fd = open(node->right->token, O_RDONLY);
		//expand here as well
		dup2(fd, STDIN_FILENO);
		node->right = node->right->right;
	}
	else if (node->type == REDIR_APPEND)
	{
		int fd;
		fd = open(node->right->token, O_WRONLY | O_APPEND | O_CREAT, 0777);
		//expand here as well
		dup2(fd, STDOUT_FILENO);
		node->right = node->right->right;
	}
}


void	process_before_right(t_ast *node, t_ctx *ctx, void **param)
{
	if (node->right == NULL) //before here was WORD not NULL
	{
			pid_t pid;
			pid = fork();

			if (pid == 0)
			{
				// char *pathname;
				// pathname = get_validpath(ctx, ctx->argv);
				execve(*(ctx->argv), ctx->argv, ctx->envp);
				exit(-1);

			}
			ft_parrclean(0, free, ctx->argv, NULL);
			ctx->argv = NULL;
			ctx->last_child = pid;
			// execv or eval (builtin) ctx->argv
	}
	else if (node->type == PIPE)
	{
		t_pipe *p;
		int fd;

		p = *param;

		//restore stdout
		fd = open(ctx->ttyname, O_RDWR);
		dup2(fd, STDOUT_FILENO);
		close(fd);

		close(p->write);

		//chenge stdin
		dup2(p->read, STDIN_FILENO);
	}
	return ;
}

void	process_on_way_back(t_ast *node, t_ctx *ctx, void **param)
{
	if (node->type == PIPE)
	{
		t_pipe *p;
		int fd;

		p = *param;

		//restore stdin
		fd = open(ctx->ttyname, O_RDWR);
		dup2(fd, STDIN_FILENO);
		close(fd);
		close_pipe(p);
	}
	else if (node->type == REDIR_OUT)
	{
		int fd;
		//restore stdin
		fd = open(ctx->ttyname, O_RDWR);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (node->type == REDIR_IN)
	{
		int fd;
		//restore stdin
		fd = open(ctx->ttyname, O_RDWR);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (node->type == REDIR_APPEND)
	{
		int fd;
		//restore stdin
		fd = open(ctx->ttyname, O_RDWR);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return ;
}



void traverse_ast(t_ast *node, t_ctx *ctx)
{
	void *param;

    if (node == NULL) //base case
	{
		return ;
	}
	else //recursicve case
	{
		param = NULL;
        process_before_left(node, ctx, &param); // Apply the function to the node when step into, before left node
        traverse_ast(node->left, ctx); // Traverse left subtree

		process_before_right(node, ctx, &param); // Apply the function to the node when left leaf visited
       	traverse_ast(node->right, ctx);  // Traverse right subtree

        // Apply the function to the node when coming back and right visited
        process_on_way_back(node, ctx, &param); //cleaning when coming back use redir node to restore FD
		free(param);
    }
	// Preorder: Could be onEntry, startNode, etc.
	// Intorcer: Could be beforeRight, midNode, etc.
	// Postorder: Could be onExit, endNode, etc.
}

