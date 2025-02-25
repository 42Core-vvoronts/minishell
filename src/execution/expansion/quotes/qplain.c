/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qplain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:06:27 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 10:14:36 by vvoronts         ###   ########.fr       */
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
	char	*value;
	char	*start;
	char	*tmp;

	char	wildcard[2] = {5, '\0'};
	char	blank = 4;

	while (**end && !is_single_quote(*end) && !is_double_quote(*end))
	{
		if (is_dollar(*end))
		{
			value = handle_variable(end, ctx);
			if (value)
			{
				tmp = value;
				while (*tmp)
				{
					if (is_blank(tmp))
						*tmp = blank;
					tmp++;
				}
				ft_strnjoin(result, value, ft_strlen(value), ctx);
			}
		}
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
	return (!is_single_quote(c) && !is_double_quote(c) && !is_dollar(c) && !is_asterisk(c));
}
