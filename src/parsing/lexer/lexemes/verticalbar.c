/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verticalbar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:33 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 10:50:07 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_vertical_bar(char *lex)
{
	if (lex && is_eqlchar(*lex, '|'))
		return (true);
	return (false);
}

void	tokenize_vertical_bar(char **lex, t_tok **tok, t_tok **cur, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lex;
	end = start;
	new = NULL;
	if (is_vertical_bar(end + 1))
		end++;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tok, cur);
	*lex = end + 1;
}
