/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:07:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/12 06:45:55 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool contain_wildcard(char *str)
// {
// 	return ((bool)ft_strchr(str ,'*'));
// }

static bool match_pattern(char *str, char *pattern, int mode)
{
	int	increment;

	if (mode == 0)
		return (match_pattern(str, pattern, 1) && match_pattern(str, pattern, -1));
	if (mode == 1)
		increment = 1;
	else if (mode == -1)
	{
		while (*(str + 1))
			str++;
		while (*(pattern + 1))
			pattern++;
		increment = -1;
	}
	while(*str && *pattern)
	{
		if (*pattern == '*')
			return (true);
		if (*str != *pattern)
			return (false);
		str += increment;
	}
	return (true);
}

// char **expand_wildcard(t_node *node)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	char			**result;

// 	dir = opendir(".");
// 	if (dir == NULL)
// 		error(-1, node->ctx, (t_m){strerror(errno)});
// 	entry = readdir(dir); //does it alocate memory for that?
// 	while (entry != NULL)
// 	{
// 		if (is_eqlstr(entry->d_name, ".") || is_eqlstr(entry->d_name, ".."))
// 		{
// 			entry = readdir(dir);
// 			continue ;
// 		}
// 		ft_parradd(result, entry->d_name);
// 		printf("d_name: %s\n", entry->d_name);
// 		// printf("d_namlen: %hu\n", entry->d_namlen);
// 		// printf("d_ino: %llu\n", entry->d_ino);
// 		printf("\n");
// 		entry = readdir(dir);
// 	}
// }

int main()
{
	printf("result: %d\n", match_pattern("dir1", "d*1", 0));
}
