/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:23:16 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 08:33:24 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_redir_in(t_node *node)
{
	int	fd;
	char	*pathname;

	evaluate_node(node->left);
	pathname = pop_arg(node);
	//ft_split result of pop arg
	fd = open(pathname, O_RDONLY);
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
