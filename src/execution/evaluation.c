/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:11:28 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:11:46 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	evaluate_node(t_node *node)
{
	if (node == NULL || node->ctx->exitcode != EXIT_SUCCESS)
	{
		return ;
	}
	if (node->type == PIPE)
	{
		process_pipe(node);
	}
	else if (node->type == REDIR_IN)
	{
		process_redir_in(node);
	}
	else if (node->type == REDIR_OUT)
	{

	}
	else if (node->type == REDIR_APPEND)
	{

	}
	else if (node->type == REDIR_HEREDOC_NOQUOTES)
	{

	}
	else if (node->type == REDIR_HEREDOC_QUOTES)
	{

	}
	else if (node->type == WORD_ZERO_QUOTES)
	{
		process_word_zero_quotes(node);
	}
	else if (node->type == WORD_SINGLE_QUOTES)
	{
		process_word_single_quotes(node);
	}
	else if (node->type == WORD_DOUBLE_QUOTES)
	{
		process_word_double_quotes(node);
	}
	else if (node->type == GROUP)
	{
		process_group(node);
	}
	else if (node->type == AND)
	{
		process_and(node);
	}
	else if (node->type == OR)
	{
		process_or(node);
	}
	else
	{
		return ;
	}
}
