/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:35:04 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 17:56:57 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	get_quotes_ctx(char *delim)
{
	return (ft_strchr(delim, '\'') || ft_strchr(delim, '"'));
}

static size_t	get_len_bare_delim(char *delim)
{
	size_t	len;

	len = 0;
	while (*delim)
	{
		if (*delim != '\'' || *delim != '"')
			len++;
		delim++;
	}
	return (len);
}

static bool	invalid_delim_error(char **delim, t_ctx *ctx, t_tok **current)
{
	tok_error(*delim, ctx);
	free(*delim);
	*current = NULL;
	return (false);
}

//returns false if delim invalid
//puts delimed cleaned of quotes into char **delim
//if there were quotes puts true into bool *quotes
bool	get_valid_delim(char **delim, t_ctx *ctx, t_tok **current, bool *quotes)
{
	char	*new_delim;
	size_t	i;
	size_t	j;

	if (!*delim || is_operator(*delim))
		return (invalid_delim_error(delim, ctx, current));
	*quotes = get_quotes_ctx(*delim);
	new_delim = ft_calloc(get_len_bare_delim(*delim) + 1, sizeof(char));
	if (!new_delim)
		error(-1, ctx, (t_m){strerror(errno)});
	i = 0;
	j = 0;
	while ((*delim)[i])
	{
		if ((*delim)[i] != '\'' && (*delim)[i] != '"')
			new_delim[j++] = (*delim)[i];
		i++;
	}
	free(*delim);
	*delim = new_delim;
	return (true);
}

char	*get_delimeter(char **lexeme, t_ctx *ctx)
{
	char	*start;
	char	*end;
	char	*delim;

	skip_blanks(lexeme);
	if (!**lexeme)
		return (tok_error(*lexeme, ctx));
	start = *lexeme;
	end = start;
	while (*end && !is_blank(end))
		end++;
	delim = ft_strndup(start, end - start);
	if (!delim)
		error(-1, ctx, (t_m){strerror(errno)});
	*lexeme = end;
	return (delim);
}
