/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 09:56:17 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//exit(1) bash: export: `=test': not a valid identifier
void	run_export(t_node *node)
{
	size_t	i;
	char	**stash;

	i = 0;
	node->ctx->exitcode = EXIT_SUCCESS;
	stash = node->ctx->stash;
	while ((node->ctx->stash)[++i])
	{
		if (!is_valid_identifier((node->ctx->stash)[i]))
		{
			error(1, node->ctx, (t_m){EXPORT, stash[i] + TOK, NOT_VALID_IDN});
			continue ;
		}
		if (!is_required_to_add((node->ctx->stash)[i]))
			continue ;
		add_var(node, (node->ctx->stash)[i]);
	}
}
