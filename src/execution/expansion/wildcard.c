/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:07:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/24 06:29:07 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	contain_wildcard(char *str)
{
	return ((bool)ft_strchr(str , 5));
}

// On success, readdir() returns a pointer to a dirent structure.
// (This structure may be statically allocated; do not attempt to free(3) it.
// scan for char after ***** 'd' and ft_strchr('d')
static	bool match_pattern(char *str, char *pattern)
{
	while(*str && *pattern)
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
	return (true);
}

//replace wildcard int 5 with asterisk *
char	*replace_wildcard(char *str, t_node *node)
{
	size_t	i;
	char *result;

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

static	void	add_filename_to_stash(t_node *node, char *filename)
{
	char *arg;

	arg = ft_strdup(filename);
	if (!arg)
		error(-1, node->ctx, (t_m){strerror(errno)});
	node->ctx->stash = ft_parradd(node->ctx->stash, arg);
}

void expand_wildcard(t_node *node, char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t	len;

	dir = opendir(".");
	if (dir == NULL)
		error(-1, node->ctx, (t_m){strerror(errno)});
	entry = readdir(dir);
	len = ft_parrlen(node->ctx->stash);
	while (entry != NULL)
	{
		if (is_eqlstr(entry->d_name, ".") || is_eqlstr(entry->d_name, ".."))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(entry->d_name, pattern))
			add_filename_to_stash(node, entry->d_name);
		entry = readdir(dir);
	}
	if (ft_parrlen(node->ctx->stash) == len)
		node->ctx->stash = ft_parradd(node->ctx->stash, replace_wildcard(pattern, node));
	if (closedir(dir) == ERROR)
		error(-1, node->ctx, (t_m){strerror(errno)});
	free(pattern);
}

void	handle_wildcard(t_node *node, char **input)
{
	size_t i;

	i = 0;
	while (input[i])
	{
		if (contain_wildcard(input[i]))
			expand_wildcard(node, input[i]);
		else
			node->ctx->stash = ft_parradd(node->ctx->stash, input[i]);
		i++;
	}
	free(input);
}

//  int main()
//  {
// 	char			**result;

// 	result = expand_wildcard(NULL);
// 	printf("\n");
// 	while (result && *result)
// 	{
// 		printf("%s\n", *result);
// 		result++;
// 	}
//  	// printf("result: %d\n", match_pattern("dir1", "D*1", 0));
//  }
