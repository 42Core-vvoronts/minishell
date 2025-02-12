/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:24 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 12:00:18 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_single_quote(char *lexeme)
{
    if (lexeme && is_eqlchar(*lexeme, '\''))
        return true;
    return false;
}

bool	is_double_quote(char *lexeme)
{
    if (lexeme && is_eqlchar(*lexeme, '\"'))
        return true;
    return false;
}

void	tokenize_quotes(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (!*lexeme)
		return ;
	if (!is_double_quote(*lexeme) && !is_single_quote(*lexeme))
		return ;
	start = *lexeme;
	end = *lexeme + 1;
	while (*end && !is_double_quote(end) && !is_single_quote(end))
		end++;
	if (!is_double_quote(end) && !is_single_quote(end))
		error_exit("Unclosed quote");
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tokens, current);
	*lexeme = end + 1;
}
