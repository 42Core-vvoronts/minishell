/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:58:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 07:49:29 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	puterr(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
}

// static char *get_msg(t_error error)
// {
// 	if (error == MALLOC)
// 		return ("malloc: allocation failed");
// 	else if (error == CMD_NOT_FOUND)
// 		return ("command not found");
// 	else if (error == FILE_NOT_FOUND)
// 		return ("No such file or directory");
// 	return ("");
// }

void error(void *data, t_datatype datatype, t_error error)
{
	(void)datatype;
	(void)error;

	ft_putstr_fd("bash: ", STDERR_FILENO);
	if (error == FILE_NOT_FOUND)
	{
		puterr(((t_node *)data)->ctx->stash[0]);
		puterr(": ");
		puterr("No such file or directory\n");
		//clean here mem and fd
		exit(1);
	}
	else if (error == PERMISSION_DENIED)
	{
		puterr(((t_node *)data)->ctx->stash[0]);
		puterr(": ");
		perror("");
		exit(1);
	}
	else if (error == CMD_NOT_FOUND)
	{
		puterr(((t_node *)data)->ctx->stash[0]);
		puterr(": ");
		puterr("command not found\n");
		exit(1);

	}
	else if (error == GENERIC)
	{
		perror("");
		exit(1);
	}
}
