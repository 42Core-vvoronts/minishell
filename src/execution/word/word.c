/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:10:13 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:10:34 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	process_word_zero_quotes(t_node *node)
{
	//expand $var and expand *
	add_arg(ft_strdup(node->token), &(node->ctx->stash));
	evaluate_node(node->right);
}

void	process_word_single_quotes(t_node *node)
{
	//expand $var and expand *
	add_arg(ft_strdup(node->token), &(node->ctx->stash));
	evaluate_node(node->right);
}

void	process_word_double_quotes(t_node *node)
{
	//expand $var and expand *
	add_arg(ft_strdup(node->token), &(node->ctx->stash));
	evaluate_node(node->right);
}
