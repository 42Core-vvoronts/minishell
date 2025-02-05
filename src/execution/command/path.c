/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:00 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 10:23:09 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	**split(char *pathval, t_node *node)
{
	char	**dirnames;

	dirnames = ft_split(pathval, ':');
	if (!dirnames)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	return (dirnames);
}

static	char	*add_slash(char	**dirnames, t_node *node, size_t i)
{
	char	*pathname;

	pathname = ft_strjoin(dirnames[i], "/");
	if (!pathname)
	{
		ft_parrclean(dirnames);
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	}
	return (pathname);
}

static	char	*add_basename(char	**dirnames, char *slashname, t_node *node)
{
	char	*pathname;

	pathname = ft_strjoin(slashname, node->ctx->stash[0]);
	free(slashname);
	if (!pathname)
	{
		ft_parrclean(dirnames);
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	}
	return (pathname);
}

static char	*retrieve_pathname(char *pathval, t_node *node)
{
	char	**dirnames;
	char	*pathname;
	size_t	i;

	dirnames = split(pathval, node);
	i = 0;
	while (dirnames[i])
	{
		pathname = add_slash(dirnames, node, i);
		pathname = add_basename(dirnames, pathname, node);
		if (!is_exist(pathname))
		{
			free(pathname);
			i++;
			continue ;
		}
		ft_parrclean(&dirnames);
		return (pathname);
	}
	return (NULL);
}

char *get_pathname(t_node *node)
{
	char	*pathname;
	char	*pathval;

	if (is_pathname(node->ctx->stash[0]))
	{
		pathname = ft_strdup(node->ctx->stash[0]);
		if (!pathname)
			error(node, STRUCT_NODE, MALLOC_FAIL, true);
		if (!is_exist(pathname))
			error(node, STRUCT_NODE, FILE_NOT_FOUND, true); // bash: ./test/lds: No such file or directory
	}
	else
	{
		pathval = get_varvalue(node->ctx, "PATH");
		if (!pathval)
			error(node, STRUCT_NODE, FILE_NOT_FOUND, true);
		pathname = retrieve_pathname(pathval, node);
		if (!pathname)
			error(node, STRUCT_NODE, CMD_NOT_FOUND, true); //exit(127); inside of error // bash: dfdf: command not found
	}
	if (is_executable(pathname))
		return (pathname);
	free(pathname);
	error(node, STRUCT_NODE, NOT_EXECUTABLE, true); // bash: ./test/ls: Permission denied
	return (NULL);
}
