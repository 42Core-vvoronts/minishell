/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:59:49 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 10:52:52 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_ampersand(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '&'))
		return (true);
	return (false);
}

bool	is_double_ampersand(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '&'))
	{
		if (*(lexeme + 1) && is_eqlchar(*(lexeme + 1), '&'))
			return (true);
	}
	return (false);
}

void	tokenize_ampersand(char **lexeme, t_tok **tok, t_tok **cur, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (!is_ampersand(end + 1))
	{
		tok_error(end + 1, ctx);
		return ;
	}
	end++;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tok, cur);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
		tok_error(*lexeme, ctx);
}
