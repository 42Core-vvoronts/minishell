/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:07:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/03/02 09:36:08 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// On success, readdir() returns a pointer to a dirent structure.
// (This structure may be statically allocated; do not attempt to free(3) it.
// scan for char after ***** 'd' and ft_strchr('d')
static	bool	match_pattern(char *str, char *pattern)
{
	while (*str && *pattern)
	{
		if (*pattern == 5)
		{
			while (*pattern == 5)
				pattern++;
			if (!*pattern)
				return (true);
			str = ft_strchr(str, *pattern);
		}
		if (!str || (*str != *pattern))
			return (false);
		str++;
		pattern++;
	}
	if (!*str && !*pattern)
		return (true);
	return (false);
}

//replace wildcard int 5 with asterisk *
char	*replace_wildcard(char *str, t_node *node)
{
	size_t	i;
	char	*result;

	i = 0;
	result = ft_strdup(str);
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno)});
	while (result [i])
	{
		if (result [i] == 5)
			result[i] = '*';
		i++;
	}
	return (result);
}

static	void	add_name_to_result(t_node *node, char *filename, char ***result)
{
	char	*arg;

	arg = ft_strdup(filename);
	if (!arg)
		error(-1, node->ctx, (t_m){strerror(errno)});
	*result = ft_parradd(*result, arg);
}

void	expand_wildcard(t_node *node, char *pattern, char ***result)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		error(-1, node->ctx, (t_m){strerror(errno)});
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(entry->d_name, pattern))
			add_name_to_result(node, entry->d_name, result);
		entry = readdir(dir);
	}
	if (*result == NULL)
		*result = ft_parradd(*result, replace_wildcard(pattern, node));
	if (closedir(dir) == ERROR)
		error(-1, node->ctx, (t_m){strerror(errno)});
	free(pattern);
}

void	handle_wildcard(t_node *node, char **input)
{
	size_t	i;
	char	**result;

	i = 0;
	result = NULL;
	while (input[i])
	{
		if (contain_wildcard(input[i]))
		{
			expand_wildcard(node, input[i], &result);
			bubble_sort(&result, ft_parrlen(result));
			node->ctx->stash = ft_parrjoin(node->ctx->stash, result);
		}
		else
			node->ctx->stash = ft_parradd(node->ctx->stash, input[i]);
		i++;
	}
	free(input);
}
