/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:00 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 09:52:21 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*add_slash(char	**dirnames, t_node *node, size_t i)
{
	char	*pathname;

	pathname = ft_strjoin(dirnames[i], "/");
	if (!pathname)
	{
		ft_parrclean(dirnames);
		error(-1, node->ctx, (t_m){strerror(errno)});
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
		error(-1, node->ctx, (t_m){strerror(errno)});
	}
	return (pathname);
}

static char	*retrieve_pathname(char *pathval, t_node *node)
{
	char	**dirnames;
	char	*pathname;
	size_t	i;

	if (node->ctx->stash[0][0] == '\0')
		return (NULL);
	dirnames = ft_split(pathval, ':');
	if (!dirnames)
		error(-1, node->ctx, (t_m){strerror(errno)});
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
	ft_parrclean(&dirnames);
	return (NULL);
}

//exit(127); bash: ./test/lds: No such file or directory
static	char	*search_filesystem(t_node *node)
{
	char	*pathname;

	pathname = ft_strdup(node->ctx->stash[0]);
	if (!pathname)
		error(-1, node->ctx, (t_m){strerror(errno)});
	if (is_exist(pathname))
		return (pathname);
	else
	{
		error(127, node->ctx, (t_m){pathname, strerror(errno)});
		free(pathname);
		return (NULL);
	}
}

//exit(127); inside of error // bash: dfdf: command not found
//exit(126); bash: ./test/ls: Permission denied
char	*get_pathname(t_node *node)
{
	char	*pathname;
	char	*pathval;

	pathname = NULL;
	if (is_pathname(node->ctx->stash[0]))
		pathname = search_filesystem(node);
	else
	{
		pathval = get_val(node->ctx, "PATH");
		if (!pathval)
		{
			error(127, node->ctx, (t_m){node->ctx->stash[0], FILE_NOT_FOUND});
			return (NULL);
		}
		pathname = retrieve_pathname(pathval, node);
		if (!pathname)
			error(127, node->ctx, (t_m){node->ctx->stash[0], CMD_NOT_FOUND});
	}
	if (!pathname)
		return (NULL);
	if (is_executable(pathname) && !is_directory(pathname))
		return (pathname);
	free(pathname);
	error(126, node->ctx, (t_m){node->ctx->stash[0], strerror(errno)});
	return (NULL);
}
