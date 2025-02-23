/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:41 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/20 12:54:40 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word_lexeme(char *lexeme)
{
    if (lexeme && (ft_isalpha(*lexeme) || ft_isdigit(*lexeme) || is_eqlchar(*lexeme, '_') ||
		is_character(lexeme)))
        return true;
    return false;
}

void	tokenize_words(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (!*lexeme || !**lexeme)
		return ;
	start = *lexeme;
	end = start;
	new = NULL;
	if (!is_word_lexeme(*lexeme))
		return ;
	start = *lexeme;
	end = start;
	while (*end && is_word_lexeme(end))
	{
		if (is_double_quote(end-1))
			double_string(&end, ctx);
		else
			single_string(&end, ctx);
		end++;
	}
	new = init_token(start, end - start, ctx);
	add_token(new, tokens, current);
	if (*end)
		*lexeme = end;
	else
		*lexeme = NULL;
}
