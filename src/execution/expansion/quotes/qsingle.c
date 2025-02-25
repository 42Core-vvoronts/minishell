/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsingle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:15:18 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 15:29:04 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process single quoted chunk of string
 *
 * @param end pointer to the current character of string
 * @param result pointer to the result string
 * @param ctx pointer to context of programm to cleanup
 *
 * @note Moves end pointer to the end of the chunk, adds chunk to result string
 */
void	single_chunk(char **end, char **result, t_ctx *ctx)
{
	if (!is_single_quote(*end))
		return ;
	(*end)++;
	while (**end)
	{
		if (is_single_quote(*end) && is_single_quote(*end - 1))
		{
			ft_strnjoin(result, "\x1D", 1, ctx);
			break ;
		}
		if (!is_single_quote(*end))
			collect_single_chars(end, result, ctx);
		else if (is_single_quote(*end))
		{
			(*end)++;
			return ;
		}
	}
	if (is_single_quote(*end))
		(*end)++;
}

void	collect_single_chars(char **end, char **result, t_ctx *ctx)
{
	char	*start;

	start = *end;
	while (**end && !is_single_quote(*end))
		(*end)++;
	ft_strnjoin(result, start, *end - start, ctx);
}
