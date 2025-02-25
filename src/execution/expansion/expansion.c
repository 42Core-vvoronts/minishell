/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:33:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 14:22:28 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process the ARGUMENT and FILENAME nodes content
 *
 * @param lexeme content of the node
 * @param ctx pointer to context of programm to cleanup
 *
 * Handle the expansion of variables and preparing wildcard expansion
 * depending on quotation of string
 *
 * @return result string with expanded variables and trimmed quotes
 */
void	expand(char **lexeme, t_ctx *ctx)
{
	char	*result;
	char	**field;
	char	*end;

	result = malloc(sizeof(char));
	if (!result)
		error(-1, ctx, (t_m){strerror(errno)});
	end = *lexeme;
	*result = '\0';
	while (*end)
	{
		double_chunk(&end, &result, ctx);
		single_chunk(&end, &result, ctx);
		plain_chunk(&end, &result, ctx);
	}
	if (result)
		ft_strnjoin(&result, "\0", 1, ctx);
	field = ft_split(result, 4);
	if (!field)
	{
		free(result);
		error(-1, ctx, (t_m){strerror(errno)});
	}
	free(result);
	handle_wildcard(ctx->head, field);
}

/**
 * @brief Process heredoc content, CONTENT node
 *
 * @param content pointer to the start character of heredoc content
 * @param ctx pointer to context of programm to cleanup
 *
 * @return result string with expanded variables
 *
 */
char	*expand_heredoc(char **content, t_ctx *ctx)
{
	char	*start;
	char	*result;
	char	*end;

	result = malloc(sizeof(char));
	if (!result)
		error(-1, ctx, (t_m){strerror(errno)});
	end = *content;
	*result = '\0';
	while (*end)
	{
		if (is_dollar(end))
			expand_variable(&end, ctx, &result);
		else if (*end && !is_dollar(end))
		{
			start = end;
			while (*end && !is_dollar(end))
				end++;
			ft_strnjoin(&result, start, end - start, ctx);
		}
	}
	if (result)
		ft_strnjoin(&result, "\0", 1, ctx);
	return (result);
}

void	ft_strnjoin(char **result, char *str, size_t len, t_ctx *ctx)
{
	char	*tmp;
	char	*mem;
	size_t	res_len;

	tmp = *result;
	res_len = ft_strlen(tmp);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	mem = malloc(res_len + len + 1);
	if (!mem)
		error(-1, ctx, (t_m){strerror(errno)});
	ft_memcpy(mem, tmp, res_len);
	ft_memcpy(mem + res_len, str, len);
	mem[res_len + len] = '\0';
	free(tmp);
	*result = mem;
}
