/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:21:17 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/11 13:00:31 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exitcode(pid_t pid)
{
	int		status;
	pid_t	child;
	int		exitcode;

	child = 0;
	exitcode = 1;
	while (child != -1)
	{
		child = wait(&status);
		if (child == pid)
		{
			if (WIFEXITED(status))
			{
				exitcode = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				exitcode = WTERMSIG(status);
			}
		}
	}
	return (exitcode);
}
