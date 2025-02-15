/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 11:00:13 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(t_node *node)
{
	size_t	i;

	i = 0;
	while (node->ctx->envp && node->ctx->envp[i])
	{
		ft_printf("%s\n", node->ctx->envp[i]);
		i++;
	}
	node->ctx->exitcode = EXIT_SUCCESS;
}
