/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:25:06 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 10:28:24 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_exist(char *pathname)
{
	return (!access(pathname, F_OK));
}

bool	is_readable(char *pathname)
{
	return (!access(pathname, R_OK));
}

bool	is_writable(char *pathname)
{
	return (!access(pathname, W_OK));
}

bool	is_executable(char *pathname)
{
	return (!access(pathname, F_OK | X_OK));
}

bool	is_pathname(char *cmd)
{
	return (ft_strchr(cmd, '/'));
}
