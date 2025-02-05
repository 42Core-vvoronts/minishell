/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:25:06 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 08:33:21 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_exist(char *pathname)
{
	return (!access(pathname, F_OK));
}

bool is_executable(char *pathname)
{
	return (!access(pathname, F_OK | X_OK));
}

bool is_pathname(char *cmd)
{
	return (ft_strchr(cmd, '/'));
}

char	*get_cmdname(void *node)
{
	return (((t_node *)node)->ctx->stash[0]);
}
