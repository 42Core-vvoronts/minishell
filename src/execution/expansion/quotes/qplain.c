/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qplain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:06:27 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 10:56:48 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process no quotes chunk of string
 *
 * @param end pointer to the current character of string
 * @param result pointer to the result string
 * @param ctx pointer to context of programm to cleanup
 *
 * @note Moves end pointer to the end of the chunk, adds chunk to result string
 */
void	plain_chunk(char **end, char **result, t_ctx *ctx)
{
	char	*start;
	char	wildcard[2];

	wildcard[0] = 5;
	wildcard[1] = '\0';
	while (**end && !is_single_quote(*end) && !is_double_quote(*end))
	{
		if (is_dollar(*end))
			expand_variable_blanks(end, ctx, result);
		if (is_asterisk(*end))
		{
			ft_strnjoin(result, wildcard, 1, ctx);
			while (is_asterisk(*end))
				(*end)++;
		}
		else if (is_plain(*end))
		{
			start = *end;
			while (**end && is_plain(*end))
				(*end)++;
			ft_strnjoin(result, start, *end - start, ctx);
		}
	}
}

bool	is_plain(char *c)
{
	if (is_blank(c) || is_single_quote(c) || is_double_quote(c)
		|| is_dollar(c) || is_asterisk(c))
		return (false);
	return (true);
}
