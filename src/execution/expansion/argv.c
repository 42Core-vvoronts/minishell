/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 05:11:47 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 05:14:54 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// //split by space?
// void prepare_argv(t_node *node)
// {
// 	size_t 	i;
// 	char **result;
// 	char **tmp;

// 	tmp = NULL;
// 	result = NULL;
// 	i = 0;
// 	while (node->ctx->stash && (node->ctx->stash)[i])
// 	{
// 		tmp = ft_split((node->ctx->stash)[i], ' ');
// 		if (!tmp)
// 		{
// 			ft_parrclean(result);
// 			error(-1, node->ctx, (t_m){strerror(errno)});
// 		}
// 		result = ft_parrjoin(result, tmp);
// 		i++;
// 	}
// 	ft_parrclean(&(node->ctx->stash));
// 	node->ctx->stash = result;
// }
