/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:06:36 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 14:53:52 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands variable and join its value to result string
 *
 * @param end pointer to the current character of string
 * @param ctx pointer to context of programm to cleanup
 * @param result pointer to the result string
 */
void	expand_variable(char **end, t_ctx *ctx, char **result)
{
	char	*value;

	get_value(end, ctx, &value);
	if (value)
		ft_strnjoin(result, value, ft_strlen(value), ctx);
}

/**
 * @brief Expands variable when blanks matter and join its value to result string
 *
 * @param end pointer to the current character of string
 * @param ctx pointer to context of programm to cleanup
 * @param result pointer to the result string
 * 
 * Swap each blank with 4 for further spliting
 */
void	expand_variable_blanks(char **end, t_ctx *ctx, char **result)
{
	char	*value;
	char	*tmp;
	char	blank;

	blank = 4;
	get_value(end, ctx, &value);
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

/**
 * @brief Get the value of the variable
 *
 * @param end pointer to the current character of string
 * @param ctx pointer to context of programm to cleanup
 *
 * @return value of the variable
 *
 * @note Moves end pointer to the end of the chunk
 */
void	get_value(char **end, t_ctx *ctx, char **value)
{
	char	*varname;
	char	*start;

	(*end)++;
	start = *end;
	if (is_queston(*end))
	{
		*value = get_val_exitcode(ctx);
		(*end)++;
	}
	else
	{
		while (**end && is_valid_varname(*end))
			(*end)++;
		if (*end - start == 0)
			*value = "$";
		else
		{
			varname = ft_strndup(start, *end - start);
			if (!varname)
				error(-1, ctx, (t_m){strerror(errno)});
			*value = get_val(ctx, varname);
			free (varname);
		}
	}
}

bool	is_valid_varname(char *c)
{
	return (ft_isalnum(*c) || is_eqlchar(*c, '_'));
}

char	*get_val_exitcode(t_ctx *ctx)
{
	static char	code[12];
	char		*code_alloc;

	code_alloc = ft_itoa(ctx->exitcode);
	if (!code_alloc)
		error(-1, ctx, (t_m){strerror(errno)});
	ft_strlcpy(code, code_alloc, sizeof(code_alloc));
	free(code_alloc);
	return (code);
}
