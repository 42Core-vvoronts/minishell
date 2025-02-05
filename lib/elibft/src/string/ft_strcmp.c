/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:44:54 by ipetrov           #+#    #+#             */
/*   Updated: 2024/11/26 11:34:45 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Compares two null-terminated strings lexicographically.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return int Returns an integer less than, equal to, or greater than zero
 *         if s1 is found, respectively, to be less than, to match, or be
 *         greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		else if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		s1++;
		s2++;
	}
	return (0);
}
