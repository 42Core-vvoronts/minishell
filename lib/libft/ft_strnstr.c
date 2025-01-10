/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:45:20 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/08 13:34:23 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	int		enough_len;
	int		full_needle;

	if (*needle == '\0')
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	while (*haystack && len)
	{
		full_needle = !ft_strncmp(haystack, needle, nlen);
		enough_len = len >= nlen;
		if (*haystack == *needle && full_needle && enough_len)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
