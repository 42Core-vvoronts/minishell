/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsingle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:15:18 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 10:15:35 by vvoronts         ###   ########.fr       */
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
	char	*start;

	if (!is_single_quote(*end))
		return ;
	(*end)++;
	while (**end && !is_single_quote(*end))
	{
		start = *end;
		while (**end && !is_single_quote(*end))
			(*end)++;
		ft_strnjoin(result, start, *end - start, ctx);
	}
	if (is_single_quote(*end))
		(*end)++;
}
