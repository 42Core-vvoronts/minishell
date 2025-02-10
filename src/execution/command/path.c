/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:00 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/10 10:50:35 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	**split(char *pathval, t_node *node)
{
	char	**dirnames;

	dirnames = ft_split(pathval, ':');
	if (!dirnames)
		error(-1, node->ctx, (t_m){strerror(errno)});
	return (dirnames);
}

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
			error(-1, node->ctx, (t_m){strerror(errno)});
		if (!is_exist(pathname))
			error(127, node->ctx, (t_m){pathname, strerror(errno)}); //exit(127); bash: ./test/lds: No such file or directory
	}
	else
	{
		pathval = get_val(node->ctx, "PATH");
		if (!pathval)
			error(127, node->ctx, (t_m){FILE_NOT_FOUND});
		pathname = retrieve_pathname(pathval, node);
		if (!pathname)
			error(127, node->ctx, (t_m){CMD_NOT_FOUND}); //exit(127); inside of error // bash: dfdf: command not found
	}
	if (is_executable(pathname))
		return (pathname);
	free(pathname);
	error(126, node->ctx, (t_m){strerror(errno)}); //exit(126); bash: ./test/ls: Permission denied
	return (NULL);
}
