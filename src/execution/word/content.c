/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:08:11 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 10:24:51 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_expansion_required(char *content)
{
	return (*content == 1);
}

void	process_content(t_node *node)
{
	char	*arg;

	if (is_expansion_required(node->token))
	{
		if (*(node->token + 1) == '\0')
			arg = ft_strdup("");
		else
		{
			arg = node->token + 1;
			arg = expand_heredoc(&arg, node->ctx);
		}
	}
	else
	{
		arg = ft_strdup(node->token);
		if (!arg)
			error(-1, node->ctx, (t_m){strerror(errno)});
	}
	add_stash(arg, node);
}
