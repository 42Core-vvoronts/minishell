/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 03:44:09 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_error_msg(t_error error)
{
	if (error == MALLOC)
		return ("malloc: allocation failed");
	else if (error == CMD_NOT_FOUND)
		return ("bash: command not found");
	else if (error == FILE_NOT_FOUND)
		return ("bash: No such file or directory");
	return ("");
}
void error(void *data, t_datatype datatype, t_error error)
{
	if (error == CMD_NOT_FOUND)
		ft_putendl_fd(get_error_msg(CMD_NOT_FOUND), STDERR_FILENO);
	if (error == GENERIC)
		perror("");
}
