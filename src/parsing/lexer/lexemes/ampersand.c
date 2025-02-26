/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:59:49 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 11:02:14 by ipetrov          ###   ########.fr       */
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

void	tokenize_ampersand(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (!is_ampersand(end + 1))
	{
		error(2, ctx, (t_m){"syntax error near unexpected token", end+1});
		return ;
	}
	end++;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
	{
		error(2, ctx, (t_m){"syntax error near unexpected token", *lexeme});
	}
}
