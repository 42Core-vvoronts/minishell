/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:06:36 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/25 10:16:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*handle_variable(char **end, t_ctx *ctx)
{
	char	*value;
	char	*varname;
	char	*start;

	(*end)++;
	start = *end;
	if (is_queston(*end))
	{
		value = get_val_exitcode(ctx);
		(*end)++;
	}
	else
	{
		while (**end && is_valid_varname(*end))
			(*end)++;
		if (*end - start == 0)
			value = "$";
		else
		{
			varname = ft_strndup(start, *end - start);
			if (!varname)
				error(-1, ctx, (t_m){strerror(errno)});
			value = get_val(ctx, varname);
			free (varname);
		}
	}
	return (value);
}

bool	is_valid_varname(char *c)
{
	return (ft_isalnum(*c) || is_eqlchar(*c, '_'));
}

char	*get_val_exitcode(t_ctx *ctx)
{
	char	*code_alloc;
	static char	code[12];
	
	code_alloc = ft_itoa(ctx->exitcode);
	if (!code_alloc)
		error(-1, ctx, (t_m){strerror(errno)});
	ft_strlcpy(code, code_alloc, sizeof(code_alloc));
	free(code_alloc);
	return (code);
}
