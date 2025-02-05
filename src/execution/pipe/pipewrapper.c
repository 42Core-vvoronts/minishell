/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipewrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:58:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:03:23 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	open_pipe(t_pipe *p)
{
	int	fd[2];

	if (pipe(fd) == ERROR)
	{
		return (1);
		// return (error(PIPE, NULL));
	}
	p->read = fd[0];
	p->write = fd[1];
	return (SUCCESS);
}

int	close_pipe(t_pipe *p)
{
	close(p->read);
	close(p->write);
	return (SUCCESS);
}
