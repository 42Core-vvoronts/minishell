/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exputils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:17:39 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/28 12:47:00 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	contain_wildcard(char *str)
{
	return ((bool)ft_strchr(str, 5));
}

// Function to swap two string pointers
static	void	swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

// Function to perform Bubble Sort on an array of strings using while loops
void	bubble_sort(char ***arr, int n)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	swapped = 1;
	while (i < n - 1 && swapped)
	{
		swapped = 0;
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
