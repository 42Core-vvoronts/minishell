/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:42:46 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 18:54:11 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	scroll_to_last(t_node **tmp, t_node **tail)
{
	while (*tmp && (*tmp)->left)
	{
		*tail = (*tmp)->left;
		*tmp = (*tmp)->left;
	}
}

static void	attach_arg(t_tok **tok, t_node **head, t_node **tail, t_ctx *ctx)
{
	t_node	*arg;

	arg = init_node(*tok, NULL, NULL, ctx);
	step_forward(tok);
	if (!*head)
	{
		*head = arg;
		*tail = arg;
	}
	else
	{
		(*tail)->left = arg;
		*tail = arg;
	}
}

void	collect_args(t_tok **tok, t_node *word, t_ctx *ctx)
{
	t_node	*head;
	t_node	*tail;
	t_node	*tmp;

	head = NULL;
	if (!word || !*tok)
		return ;
	tmp = word;
	if (tmp && tmp->left)
		head = tmp->left;
	tail = head;
	while (tmp && tmp->left)
		scroll_to_last(&tmp, &tail);
	while (*tok && is_word_token(*tok))
		attach_arg(tok, &head, &tail, ctx);
	word->left = head;
}
