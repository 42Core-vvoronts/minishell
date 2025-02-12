/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:07:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 12:55:22 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool contain_wildcard(char *str)
{
	return ((bool)ft_strchr(str ,'*'));
}

// On success, readdir() returns a pointer to a dirent structure.
// (This structure may be statically allocated; do not attempt to free(3) it.
static bool match_pattern(char *str, char *pattern)
{
	while(*str && *pattern)
	{
		if (*pattern == '*')//scan for char after ***** 'd' and ft_strchr('d')
		{
			while (*pattern == '*')
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

char **expand_wildcard(t_node *node)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**result;

	dir = opendir(".");
	if (dir == NULL)
		error(-1, node->ctx, (t_m){strerror(errno)});
	entry = readdir(dir); //check errno for errors
	result = NULL;
	while (entry != NULL)
	{
		if (is_eqlstr(entry->d_name, ".") || is_eqlstr(entry->d_name, ".."))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(entry->d_name, "sle*p*r*t*c"))
			result = ft_parradd(result, entry->d_name);
		entry = readdir(dir); //check errno for errors
	}
	if (closedir(dir) == ERROR)
		error(-1, node->ctx, (t_m){strerror(errno)});
	return (result);
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
