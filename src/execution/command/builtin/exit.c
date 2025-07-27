/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:56:55 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/28 03:24:02 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

//LONG_MAX = 9223372036854775807
//LONG_MIN = -9223372036854775808  
static	bool	is_valid_long_str(char *str)
{
	bool	negative;
	char	*num_part;
	size_t	len;
	
	negative = (str[0] == '-');
	num_part = str + (str[0] == '-' || str[0] == '+');
	len = ft_strlen(num_part);
	
	// More than 19 digits is definitely overflow
	if (len > 19)
		return (false);
	
	// Less than 19 digits is definitely valid
	if (len < 19)
		return (true);
	
	// Exactly 19 digits: need careful comparison
	if (negative)
	{
		// Compare against 9223372036854775808 (absolute value of LONG_MIN)
		return (ft_strcmp(num_part, "9223372036854775808") <= 0);
	}
	else
	{
		// Compare against 9223372036854775807 (LONG_MAX)
		return (ft_strcmp(num_part, "9223372036854775807") <= 0);
	}
}

static	bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	
	// Check if all characters are digits
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	
	// Check if it's within long range
	return (is_valid_long_str(str));
}

static	long	parse_long(char *str, bool *overflow)
{
	long	result;
	long	sign;
	size_t	i;

	*overflow = false;
	result = 0;
	sign = 1;
	i = 0;
	
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	
	// Special case for LONG_MIN which can't be represented as positive
	if (sign == -1 && ft_strcmp(str + 1, "9223372036854775808") == 0)
		return (LONG_MIN);
	
	while (str[i])
	{
		// Check for overflow before multiplication
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = true;
			return (sign > 0 ? LONG_MAX : LONG_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static	int	evaluate_exitcode(t_node *node)
{
	long	exit_val;
	bool	overflow;

	if (!is_numeric(node->ctx->stash[1]))
	{
		error(2, node->ctx, (t_m){EXIT, node->ctx->stash[1], EXIT_NON_NUM});
		return (2);
	}
	
	exit_val = parse_long(node->ctx->stash[1], &overflow);
	if (overflow)
	{
		error(2, node->ctx, (t_m){EXIT, node->ctx->stash[1], EXIT_NON_NUM});
		return (2);
	}
	
	// Exit code is the low 8 bits (modulo 256)
	return ((int)(exit_val & 0xFF));
}

void	run_exit(t_node *node)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (node->ctx->stash && node->ctx->stash[1])
	{
		if (node->ctx->stash[2])
		{
			error(1, node->ctx, (t_m){EXIT, TOO_MANY_ARG});
			return ;
		}
		else if (is_eqlstr(node->ctx->stash[1], "--"))
			node->ctx->exitcode = EXIT_SUCCESS;
		else
			node->ctx->exitcode = evaluate_exitcode(node);
	}
	exit(allclean(node, FULL));
}
