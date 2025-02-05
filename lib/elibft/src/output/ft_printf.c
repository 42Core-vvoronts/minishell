/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 07:55:34 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 13:29:09 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Recursively prints a number in a given base.
 * @param n The number to print.
 * @param base The base to print the number in.
 * @param radix The characters representing the digits in the base.
 * @return The number of characters printed.
 */
int	word(size_t n, size_t base, char *radix)
{
	int	len;

	len = 0;
	if (n < base)
		return (write(1, &radix[n], 1), 1);
	len += word(n / base, base, radix);
	len += word(n % base, base, radix);
	return (len);
}

/**
 * Prints a number with special handling for integers and pointers.
 * @param n The number to print.
 * @param base The base to print the number in.
 * @param radix The characters representing the digits in the base.
 * @param type The type of the number ('i' for integer, 'p' for pointer).
 * @return The number of characters printed.
 */
int	number(size_t n, size_t base, char *radix, char type)
{
	int	i;

	i = 0;
	if (type == 'i')
	{
		i = (int)n;
		if (i < 0)
		{
			write(1, "-", 1);
			n = (size_t) ~ i + 1;
			i = 1;
		}
		else
			i = 0;
	}
	else if (type == 'p')
	{
		if (n == 0)
			return (write(1, "(nil)", 5), 5);
		write(1, "0x", 2);
		i = 2;
	}
	return (word(n, base, radix) + i);
}

/**
 * Prints a string.
 * @param s The string to print.
 * @return The number of characters printed.
 */
int	string(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6), 6);
	while (s[len])
		len++;
	write(1, s, len);
	return (len);
}

/**
 * Handles the format specifier and prints the corresponding argument.
 * @param spc The format specifier.
 * @param args The list of arguments.
 * @return The number of characters printed.
 */
int	handler(char spc, va_list args)
{
	int	len;

	len = 0;
	if (spc == '%' && ++len)
		write(1, &spc, 1);
	else if (spc == 'c' && ++len)
	{
		spc = (char)va_arg(args, int);
		write(1, &spc, 1);
	}
	else if (spc == 's')
		len = string((char *)va_arg(args, char *));
	else if (spc == 'p')
		len = number((size_t)va_arg(args, void *), 16, "0123456789abcdef", 'p');
	else if (spc == 'd' || spc == 'i')
		len = number((size_t)va_arg(args, int), 10, "0123456789", 'i');
	else if (spc == 'u')
		len = number((size_t)va_arg(args, unsigned int), 10, "0123456789", 'u');
	else if (spc == 'x')
		len = number(va_arg(args, unsigned int), 16, "0123456789abcdef", 'u');
	else if (spc == 'X')
		len = number(va_arg(args, unsigned int), 16, "0123456789ABCDEF", 'u');
	return (len);
}

/**
 * A custom implementation of printf.
 * @param fstr The format string.
 * @return The number of characters printed.
 */
int	ft_printf(const char *fstr, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, fstr);
	while (*fstr)
	{
		if (*fstr == '%')
			len += handler(*(++fstr), args);
		else
		{
			write (1, fstr, 1);
			len++;
		}
		fstr++;
	}
	va_end(args);
	return (len);
}
