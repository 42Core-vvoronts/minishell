/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipewrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:58:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 10:24:36 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	open_pipe(t_pipe *p, t_node *node)
{
	int	fd[2];

	if (pipe(fd) == ERROR)
		error(-1, node->ctx, (t_m){strerror(errno), NULL});
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
