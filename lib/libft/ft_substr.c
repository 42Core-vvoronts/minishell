/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:52:16 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/06 19:31:06 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_substr(const char *s, int start, size_t len)
{
	size_t			slen;
	char			*ptr;
	unsigned int	ustart;

	ustart = start;
	slen = ft_strlen(s);
	if (ustart >= slen)
		return (ft_strdup(""));
	if (len > slen - ustart)
		len = slen - ustart;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
