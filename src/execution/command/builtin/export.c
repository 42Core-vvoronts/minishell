/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 07:01:03 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static	bool	is_required_to_add(char *str)
{
	return (ft_strchr(str, '='));
}

static	bool	is_valid_identifier(char *str)
{
	if (*str == '=' || ft_isdigit(*str))
		return (false);
	while (*str != '=' && *str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void	run_export(t_node *node)
{
	size_t	i;

	i = 0;
	while ((node->ctx->stash)[++i])
	{
		if (!is_valid_identifier((node->ctx->stash)[i]))
		{
			add_msg((node->ctx->stash)[i], node);
			add_msg(NOT_VALID_IDENTIFIER, node);
			error(node, MINISHELL, false);
			continue ;
		}
		if (!is_required_to_add((node->ctx->stash)[i]))
			continue ;
		add_var(node, (node->ctx->stash)[i]);
		node->ctx->exitcode = EXIT_SUCCESS;
	}
	// run_env(node);
}
