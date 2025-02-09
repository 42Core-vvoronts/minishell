/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:19:56 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 01:20:06 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_arg(char *arg, char * **stash)
{
	size_t	i;
	char **result;

	i = ft_parrlen(*stash);
	result = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*stash)[i])
	{
		result[i] = (*stash)[i];
		i++;
	}
	result[i] = arg;
	i++;
	result[i] = NULL;
	free(*stash);
	*stash = result;
}

char	*pop_arg(char * **stash)
{
	size_t	i;
	char **result;
	char *arg;

	i = ft_parrlen(*stash);
	result = malloc(sizeof(char *) * i);
	i = 0;
	while ((*stash)[i + 1])
	{
		result[i] = (*stash)[i];
		i++;
	}
	result[i] = NULL;
	arg = (*stash)[i];
	free(*stash);
	*stash = result;
	return (arg);
}

char **get_argv(char * **args)
{
	size_t 	i;
	char **result;
	char **tmp;

	tmp = NULL;
	result = NULL;
	i = 0;
	while ((*args)[i])
	{
		tmp = ft_split((*args)[i], ' ');
		result = ft_parrjoin(result, tmp);
		i++;
	}
	ft_parrclean(args);
	return (result);
}
