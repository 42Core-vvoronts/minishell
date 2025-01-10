/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:54:57 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/08 10:17:17 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	*result = '\0';
	return (result);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	size_t	start;
	size_t	end;
	size_t	reslen;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (empty_string());
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	reslen = end - start + 1;
	if (reslen == 0)
		return (empty_string());
	result = (char *)malloc(sizeof(char) * reslen + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[start], reslen + 1);
	return (result);
}
