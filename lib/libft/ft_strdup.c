/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:45:20 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/08 11:17:31 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*result;

	slen = ft_strlen(s);
	if (slen == 0)
	{
		result = (char *)malloc(sizeof(char) * 1);
		if (!result)
			return ((void *)0);
		*result = '\0';
		return (result);
	}
	result = (char *)malloc(slen + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, slen + 1);
	return (result);
}
