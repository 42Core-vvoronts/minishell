/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:08:11 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 11:11:49 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool is_expand_required(char *content)
{
	return (*content == 1);
}

void	process_content(t_node *node)
{
	char *arg;

	if (is_expand_required(node->token))
	{
		arg = node->token + 1;
		arg = expand_heredoc(&arg, node->ctx);
	}
	else
	{
		arg = ft_strdup(node->token);
		if (!arg)
			error(-1, node->ctx, (t_m){strerror(errno)});
	}
	add_stash(arg, node);
}
