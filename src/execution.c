/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:01:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/01/20 14:32:48 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_before_left(t_ast *node, void **param)
{
	if (node->type == PIPE)
	{
		printf("PIPE left\n");
	}
}

void	process_before_right(t_ast *node, void **param)
{
	return ;
}

void	process_on_way_back(t_ast *node, void **param)
{
	if (node->type == PIPE)
	{
		printf("PIPE way_back\n");
	}
	return ;
}

void traverse_ast(t_ast *node)
{
	void *param;

    if (node == NULL)//base case
	{
		return ;
	}
	else//recursicve case
	{
		// Apply the function to the node when step into, before left node
        process_before_left(node, &param);

        // Traverse left subtree
        traverse_ast(node->left);
		// Apply the function to the node when left leaf visited
		process_before_right(node, &param);

        // Traverse right subtree
       	traverse_ast(node->right);
        // Apply the function to the node when coming back and right visited
        process_on_way_back(node, &param); //cleaning when coming back use redir node to restore FD
    }
}
