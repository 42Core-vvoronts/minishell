/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:41 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 14:28:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_words(char **lexeme, t_tok **tokens, t_tok **cur, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (ctx->errlex == true || !*lexeme || !**lexeme)
		return ;
	start = *lexeme;
	end = start;
	new = NULL;
	if (!is_word_lexeme(*lexeme) && !is_double_quote(*lexeme)
		&& !is_single_quote(*lexeme))
		return ;
	while (*end)
	{
		if (is_blank(end) || is_operator(end))
			break ;
		if (is_single_quote(end) || is_double_quote(end))
			tokenize_quotes(&end, ctx);
		else
			end++;
	}
	if (ctx->errlex == true)
		return ;
	new = init_token(start, end - start, ctx);
	add_token(new, tokens, cur);
	*lexeme = end;
}
