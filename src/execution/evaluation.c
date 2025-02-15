/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:11:28 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 11:06:05 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	evaluate(t_node *node)
{
	if (node == NULL)
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
	else if (node->type == FILENAME)
		process_filename(node);
	else if (node->type == GROUP)
		process_group(node);
	else if (node->type == AND)
		process_and(node);
	else if (node->type == OR)
		process_or(node);
}
