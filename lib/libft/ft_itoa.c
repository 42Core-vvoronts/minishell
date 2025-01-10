/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:48:14 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/04 09:11:35 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				len;
	int				is_negative;
	char			*str;

	len = get_num_len(n);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	is_negative = n < 0;
	num = n;
	if (is_negative)
		num = -n;
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = num % 10 + '0';
		num /= 10;
	}
	if (is_negative)
		str[0] = '-';
	return (str);
}
