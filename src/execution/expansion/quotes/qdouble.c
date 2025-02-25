/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qdouble.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:14:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 10:15:09 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process double quoted chunk of string
 *
 * @param end pointer to the current character of string
 * @param result pointer to the result string
 * @param ctx pointer to context of programm to cleanup
 *
 * @note Moves end pointer to the end of the chunk, adds chunk to result string
 */
void	double_chunk(char **end, char **result, t_ctx *ctx)
{
	char	*value;
	char	*start;

	if (!is_double_quote(*end))
		return ;
	(*end)++;
	while (**end && !is_double_quote(*end))
	{
		if (is_dollar(*end))
		{
			value = handle_variable(end, ctx);
			if (value)
				ft_strnjoin(result, value, ft_strlen(value), ctx);
		}
		else if (!is_double_quote(*end))
		{
			start = *end;
			while (*end && !is_double_quote(*end) && !is_dollar(*end))
				(*end)++;
			ft_strnjoin(result, start, *end - start, ctx);
		}
		else if (is_double_quote(*end))
		{
			(*end)++;
			return ;
		}
	}
	if (is_double_quote(*end))
		(*end)++;
}
