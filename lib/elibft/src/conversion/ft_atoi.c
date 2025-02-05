/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:48:47 by ipetrov           #+#    #+#             */
/*   Updated: 2024/11/27 14:19:41 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

static int	get_valid_digit(char c, int base, int *digit, int *status)
{
	int	max_digit;

	if (!c || *status == FAIL)
		return (FAIL);
	c = ft_toupper(c);
	if (base <= 10)
		max_digit = base - 1 + '0';
	else
		max_digit = base - 10 - 1 + 'A';
	if (c >= '0' && c <= '9' && c <= max_digit)
		*digit = 0 + c - '0';
	else if (c >= 'A' && c <= 'F' && c <= max_digit)
		*digit = 10 + c - 'A';
	else
	{
		*status = FAIL;
		return (*status);
	}
	return (SUCCESS);
}

static char	*skip(char *str, int base, int *sign)
{
	if (!*str)
		return (str);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	*sign = 777;
	if (*str == '+')
	{
		*sign = 1;
		str++;
	}
	else if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	if (base == 16)
	{
		if (*str == '#' && *sign == 777)
			str++;
		else if (*str == '0' && *(str + 1) == 'x' && *sign == 777)
			str += 2;
	}
	*sign = 1 + (-2 * (*sign < 0));
	return (str);
}

static size_t	catch_overflow(size_t result, int digit, int *sign, int *status)
{
	size_t	new_result;

	new_result = result + digit;
	if (*sign > 0 && new_result > INT_MAX)
		*status = FAIL;
	else if (*sign < 0 && new_result > (size_t)INT_MAX + 1)
		*status = FAIL;
	return (new_result);
}

/**
 * @brief Converts a string to a long long integer with status handling.
 * 	For now handles only signed int;
 *   0 - Umbrella FAIL
 *   1 - SUCCESS
 *
 * 	All other codes currently doesnt work;
 *  -1 - Negative
 * 	 3 - Empty
 * 	 3 - Nonnumeric
 * 	 2 - 1 byte signed overflow
 * 	 2 - 1 byte unsigned overflow
 * 	 2 - 2 bytes long overflow
 * 	 2 - 4 bytes overflow, INT overflow
 * 	 2 - 8 bytes overflow, INT overflow
 *
 *	???if (sizeof(size_t) != size_of)
 *		result = result << ((sizeof(size_t) - size_of) * 8);
 *
 * @param str The input string.
 * @param status Pointer to an integer to store status codes.
 * @return long long The converted long long integer.
 */
int	ft_atoi(char *str, void *number, size_t size_of, int base)
{
	int		status;
	size_t	result;
	int		digit;
	int		sign;
	char	*mem;

	if (!str || !number || !size_of || base < 2 || base > 16)
		return (FAIL);
	str = skip(str, base, &sign);
	status = SUCCESS;
	result = 0;
	mem = str;
	--str;
	while (get_valid_digit(*++str, base, &digit, &status))
		result = catch_overflow(result * base, digit, &sign, &status);
	if (str == mem || status == FAIL)
		return (FAIL);
	if (sign < 0)
		result = (~result) + 1;
	ft_memcpy(number, &result, size_of);
	return (status);
}
