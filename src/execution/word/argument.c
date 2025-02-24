/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:10:13 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 06:58:09 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_argument(t_node *node)
{
	expand(&(node->token), node->ctx);
	if (node->left)
		evaluate(node->left);
	else
		run_cmd(node);
}
