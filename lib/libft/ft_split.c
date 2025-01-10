/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:51:49 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/08 11:32:57 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **result, int len)
{
	char	**head;

	head = result;
	while (len)
	{
		free(*result);
		result++;
		len--;
	}
	free(head);
	return (NULL);
}

static int	count_parts(char const *s, char c)
{
	int	parts;

	parts = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			parts++;
			while (*s && *s != c)
				s++;
		}
	}
	return (parts);
}

static char	*copy_part(char const **s, char c, char *part)
{
	int			len;
	char const	*head;

	len = 0;
	while (**s)
	{
		if (**s == c)
			(*s)++;
		else
		{
			head = *s;
			while (**s && **s != c)
			{
				len++;
				(*s)++;
			}
			break ;
		}
	}
	part = (char *)malloc(sizeof(char) * (len + 1));
	if (!part)
		return (NULL);
	ft_memcpy(part, head, len);
	part[len] = '\0';
	return (part);
}

char	**ft_split(char const *s, char c)
{
	int		parts;
	int		counter;
	char	**result;
	char	**head;

	if (!s)
		return (NULL);
	parts = count_parts(s, c);
	result = (char **)malloc(sizeof(char *) * (parts + 1));
	if (!result)
		return (NULL);
	head = result;
	counter = parts;
	while (counter)
	{
		*result = copy_part(&s, c, *result);
		if (!*result)
			return (ft_free(head, (parts - counter)));
		result++;
		counter--;
	}
	*result = NULL;
	return (head);
}
