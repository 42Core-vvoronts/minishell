/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qdouble.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:14:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 15:28:33 by vvoronts         ###   ########.fr       */
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
	if (!is_double_quote(*end))
		return ;
	(*end)++;
	while (**end)
	{
		if (is_double_quote(*end) && is_double_quote(*end - 1))
		{
			ft_strnjoin(result, "\x1D", 1, ctx);
			break ;
		}
		if (is_dollar(*end))
			expand_variable(end, ctx, result);
		else if (!is_double_quote(*end))
			collect_double_chars(end, result, ctx);
		else if (is_double_quote(*end))
		{
			(*end)++;
			return ;
		}
	}
	if (is_double_quote(*end))
		(*end)++;
}

void	collect_double_chars(char **end, char **result, t_ctx *ctx)
{
	char	*start;

	start = *end;
	while (*end && !is_double_quote(*end) && !is_dollar(*end))
		(*end)++;
	ft_strnjoin(result, start, *end - start, ctx);
}
