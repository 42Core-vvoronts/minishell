/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:11:28 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/09 12:40:09 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	evaluate(t_node *node)
{
	if (node == NULL || node->ctx->exitcode != EXIT_SUCCESS)
		return ;
	else if (node->type == PIPE)
		process_pipe(node);
	else if (node->type == REDIR_IN)
		process_redir_in(node);
	else if (node->type == REDIR_OUT)
		process_redir_out(node);
	else if (node->type == REDIR_APPEND)
		process_redir_append(node);
	else if (node->type == REDIR_HEREDOC)
		process_redir_heredoc(node);
	else if (node->type == ARGUMENT)
		process_argument(node);
	else if (node->type == CONTENT)
		process_content(node);
	else if (node->type == GROUP)
		process_group(node);
	else if (node->type == AND)
		process_and(node);
	else
		process_or(node);
}
