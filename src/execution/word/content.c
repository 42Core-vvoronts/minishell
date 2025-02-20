/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:08:11 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/20 04:16:00 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_content(t_node *node)
{
	char *arg;

	//expand $var and expand *
	arg = ft_strdup(node->token);
	if (!arg)
		error(-1, node->ctx, (t_m){strerror(errno), NULL});
	add_stash(arg, node);
}