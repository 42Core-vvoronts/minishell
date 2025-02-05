/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:09:00 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/05 02:14:26 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char *get_varvalue(t_ctx *ctx, char *varname)
// {
// 	char	**envp;
// 	char	*value;
// 	size_t	len;

// 	envp = ctx->envp;
// 	len = ft_strlen(varname);
// 	while (*envp)
// 	{
// 		value = ft_strnstr(*envp, varname, len);
// 		if (value)
// 		{
// 			return (value + len + 1);
// 		}
// 		envp++;
// 	}
// 	return (NULL);
// }

// bool is_executable(char *pathname)
// {
// 	return (!access(pathname, F_OK | X_OK));
// }

// bool is_pathname(char *cmd)
// {
// 	return (ft_strchr(cmd, '/'));
// }

// void remove_dirname(char **argv)
// {
// 	*argv = ft_strrchr(*argv, '/') + 1;
// }

// //impossile to understand if malloc fail or no any valid paths
// //TODO: create different exit errot handlers with memory cleaning
// char *retrieve_pathname(char *path, char *basename)
// {
// 	char **dirname;
// 	char *pathname;
// 	size_t	i;

// 	if (!path)
// 		return (NULL);
// 	dirname = ft_split(path, ':');
// 	if (!dirname)
// 	{
// 		return (FAIL);
// 	}
// 	i = 0;
// 	while (dirname[i])
// 	{
// 		pathname = ft_strjoin(dirname[i], "/");
// 		//fix here
// 		pathname = ft_strjoin(pathname, basename);
// 		if (!pathname)
// 		{
// 			return ((void *)ft_parrclean(FAIL, free, dirname, NULL));
// 		}
// 		if (is_executable(pathname))
// 		{
// 			return (pathname);
// 		}
// 		free(pathname);
// 		i++;
// 	}
// 	return (NULL);
// }

// char *get_validpath(t_ctx *ctx, char **argv)
// {
// 	char *pathname;

// 	if (is_pathname(argv[0]))
// 	{
// 		pathname = argv[0];
// 		remove_dirname(argv); //move to another place
// 		if (is_executable(pathname))
// 			return (pathname);
// 		else
// 			return (NULL);
// 	}
// 	else
// 	{
// 		pathname = retrieve_pathname(get_varvalue(ctx, "PATH"), argv[0]);
// 		if (!pathname)
// 			return (FAIL);
// 		return (pathname);
// 	}
// 	if (!pathname)
// 	{
// 		error(ctx, CMD_NOT_FOUND);
// 		return (FAIL);
// 	}
// 	return (NULL);
// }
