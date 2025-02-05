/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:05:33 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:53:03 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *init_testcase_forward(void);
void save_tree(t_node *node);

int	main(int argc, char **argv, char **envp)
{
	t_node *node;
	pid_t	pid;
	(void)pid;
	(void)argc;
	(void)argv;
	(void)envp;

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
