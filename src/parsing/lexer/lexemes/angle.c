/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:01 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 10:53:20 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_less(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '<'))
		return (true);
	return (false);
}

bool	is_greater(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '>'))
		return (true);
	return (false);
}

void	tokenize_angles(char **lexeme, t_tok **tok, t_tok **cur, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (is_less(end))
		;
	else if (is_greater(end + 1))
		end++;
	new = init_token(start, end - start + 1, ctx);
	add_token(new, tok, cur);
	*lexeme = end + 1;
}
