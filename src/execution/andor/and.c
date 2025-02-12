/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:09:28 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 03:46:33 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_and(t_node	*node)
{
	evaluate(node->left);
	if (node->ctx->exitcode == EXIT_SUCCESS && g_signal == SIGNO)
		evaluate(node->right);
}
