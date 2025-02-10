/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:11:28 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 09:59:00 by vvoronts         ###   ########.fr       */
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
		process_word(node);
	else if (node->type == CONTENT)
		process_content(node);
	else if (node->type == GROUP)
		process_group(node);
	else if (node->type == AND)
		process_and(node);
	else
		process_or(node);
}
