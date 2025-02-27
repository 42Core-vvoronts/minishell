/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:07:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/26 10:35:02 by ipetrov          ###   ########.fr       */
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

static	void	add_filename_to_result(t_node *node, char *filename, char ***result)
{
	char *arg;

	arg = ft_strdup(filename);
	if (!arg)
		error(-1, node->ctx, (t_m){strerror(errno)});
	*result = ft_parradd(*result, arg);
}

void expand_wildcard(t_node *node, char *pattern, char ***result)
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
			add_filename_to_result(node, entry->d_name, result);
		entry = readdir(dir);
	}
	if (*result == NULL)
		*result = ft_parradd(*result, replace_wildcard(pattern, node));
	if (closedir(dir) == ERROR)
		error(-1, node->ctx, (t_m){strerror(errno)});
	free(pattern);
}

// Function to swap two string pointers
static void swap(char **str1, char **str2)
{
    char *temp;

	temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

// Function to perform Bubble Sort on an array of strings using while loops
static void bubble_sort(char ***arr, int n)
{
    int i;
    int swapped;

	i = 0;
	swapped = 1;
    while (i < n - 1 && swapped)
	{
        swapped = 0;
        int j;
		j = 0;
        while (j < n - i - 1)
		{
            if (ft_strcmp((*arr)[j], (*arr)[j + 1]) > 0)
			{
                swap(&(*arr)[j], &(*arr)[j + 1]);
                swapped = 1;
            }
            j++;
        }
        i++;
    }
}

void	handle_wildcard(t_node *node, char **input)
{
	size_t i;
	char**	result;

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
