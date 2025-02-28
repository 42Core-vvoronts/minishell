/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 10:55:06 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_open_parenthesis(char *lex)
{
	if (lex && is_eqlchar(*lex, '('))
		return (true);
	return (false);
}

bool	is_close_parenthesis(char *lex)
{
	if (lex && is_eqlchar(*lex, ')'))
		return (true);
	return (false);
}

void	tokenize_parenthesis(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lex;
	end = start;
	new = NULL;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tok, cur);
	*lex = end + 1;
}
