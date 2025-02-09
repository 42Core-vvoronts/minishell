/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:52:56 by ipetrov           #+#    #+#             */
/*   Updated: 2024/11/27 12:05:06 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Computes the length of the string.
 *
 * This function takes a constant character pointer as input and returns the
 * length of the string. If the input string is NULL, it returns 0.
 *
 * @param str The input string whose length is to be computed.
 * @return The length of the input string, or 0 if the input string is NULL.
 */
size_t	ft_strlen(const char *str)
{
	const char	*mem;

	if (!str)
		return (0);
	mem = str;
	while (*str)
		str++;
	return (str - mem);
}
