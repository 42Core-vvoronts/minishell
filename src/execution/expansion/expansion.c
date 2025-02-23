/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:33:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/23 19:59:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char *c)
{
	return (ft_isalnum(c) || is_eqlchar(c, '_'));
}

void	double_chunk(char **end, char **result)
{
	(*end)++;
	while (**end && !is_double_quote(*end))
	{
		if (is_single_quote(*end))
		{
			// result = "\'"
			single_chunk(end, result);
			// result = "\'"
		}
		else if (is_dollar(*end))
			variable_chunk(end, result);
		else
			(*end)++;
	}
}

void	single_chunk(char **end, char **result)
{
	(*end)++;
	while (**end && !is_single_quote(*end))
	{
		// result = "\""
		double_chunk(end, result);
		// result = "\""
	}
}

void	plain_chunk(char **end, char **result)
{
	char	*value;
	char	*varname;
	char	*start;

	t_ctx *ctx;

	while (*end && !is_single_quote(*end) && !is_double_quote(*end))
	{
		if (is_dollar(*end))
		{
			(*end)++;
			start = *end;
			while (*end && is_valid_var_char(*end))
				(*end)++;
			varname = ft_strndup(start, *end - start - 1);
			if (!varname)
				error(-1, ctx, (t_m){strerror(errno)});
			value = get_val(ctx, varname);
		}
		if (is_asterisk(*end))
		{
			(*end)++;
		}
		else if (!is_single_quote(*end) && !is_double_quote(*end))
		{
			(*end)++;
		}
	}	
}

// char	**expand(char *lexeme, t_ctx *ctx);
void	expand()
{
	char	*lexeme = "\"a*$VAR\"$VAR2'alira'b*\"cc*c\"";
	char	**result;
	char	*end;

	end = *lexeme;
	result = malloc(sizeof(char));
	// if (!result)
	*result = '\0';
	while (*end)
	{
		if (is_double_quote(end))
			double_chunk(&end, &result);
		else if (is_single_quote(end))
			single_chunk(&end, &result);
		else
			plain_chunk(&end, &result);
	}
	printf("%s", result);
	// return (result);
}