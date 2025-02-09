/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 07:22:11 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pipe_content(t_pipe p)
{
	char c;

	while(read(p.read, &c, 1))
	{
		if (c == 4)
			break ;
		write(1, &c, 1);
	}
}

void	collect_heredoc(char *delim)
{
	char	*line;
	t_pipe	p;
	char	eot;

	// evaluate_node(node->left);
	// delim = pop_arg(node); //getfd here
	//delim remove quotes
	open_pipe(&p, NULL);
	eot = 4;
	while (1)
	{
		line = readline("> ");
		if (!line || is_eqlstr(line, delim))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, p.write);
		ft_putchar_fd('\n', p.write);
		free(line);
	}
	write(p.write, &eot, 1);
	dup2(p.read, STDIN_FILENO);
	char **envp = malloc(sizeof(char *));
	execve("/bin/cat", envp, envp);
	print_pipe_content(p);
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*node;
	t_ctx	*ctx;
	pid_t	pid;

	(void)pid;
	(void)argc;
	(void)argv;
	(void)envp;
	(void)ctx;
	(void)node;

	add_history("test");
	collect_heredoc("EOF");

	// t_pipe p;
	// open_pipe(&p, NULL);
	// char *buf = malloc(1000);
	// char str;
	// str = 4;
	// ft_putstr_fd("test line", p.write);
	// write(p.write, &str, 1);
	// int b = read(p.read, buf, 1000);
	// (void)b;

	// char *line = readline("> ");
	// printf("%s", line);
	// (void)line;

	// init_ctx(&ctx, envp);
	// // node = init_testcase_forward(ctx);

	// node->ctx->stash = malloc(sizeof(char *) * 10);
	// node->ctx->stash[0] = "cd";
	// node->ctx->stash[1] = ft_strdup("/home/ivan/perm_not_dir/../../");
	// node->ctx->stash[2] = NULL;
	// node->ctx->stash[3] = ft_strdup("TEST3");
	// node->ctx->stash[4] = NULL;

	// // run_export(node);
	// run_cd(node);

	// // save_tree(node);
	// // evaluate_node(node);
	// // printf("Result VAR: %s\n", get_var(ctx, "PATH"));
	// // printf("Result VAL: %s\n", get_val(ctx, "HOME"));

	// // char *input;

	// // while (1)
	// // {
	// // 	input = readline("prompt: ");
	// // 	add_history(input);
	// // 	rl_on_new_line(); //?????
	// // 	parse(input);
	// // 	init_ctx(&ctx, envp);
	// // 	node = init_testcase_forward(ctx);
	// 	// evaluate_node(node);
	// // 	restore_std(node);
	// printf("exitcode: %d\n", node->ctx->exitcode);
	// }
	// 	allclean(node);
	// save_tree(node);

	// (void)input;

	// //start from process_group? group = init prompt
	// // while (1)
	// // {
	// // 	//get_prompt() / get_tree() //readline here

	// // }
	return (EXIT_SUCCESS);
}
