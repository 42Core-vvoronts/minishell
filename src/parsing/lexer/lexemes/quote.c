/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:24 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/15 11:29:01 by vvoronts         ###   ########.fr       */
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

void	single_string(char **end, t_ctx *ctx)
{
	while (**end && !is_single_quote(*end))
		(*end)++;
	if (!is_single_quote(*end))
		error(2, ctx, (t_m){"Expected", "\'"});
}

void	double_string(char **end, t_ctx *ctx)
{
	while (**end && !is_double_quote(*end))
		(*end)++;
	if (!is_double_quote(*end))
		error(2, ctx, (t_m){"Expected", "\""});
}

// quotes need splited with space and only space
// Only other operators work wthout blank eg:
// "ls""-la" doesn't work without space
// "ls" "-la" works
// "ls">file.txt work because of redirection
void tokenize_quotes(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
    char    *start;
    char    *end;
    t_tok   *new;

    if (!*lexeme || (!is_double_quote(*lexeme) && !is_single_quote(*lexeme)))
        return;
    
    start = *lexeme;
    end = start + 1;
    
    if (is_double_quote(start))
        double_string(&end, ctx);
    else
        single_string(&end, ctx);
    
    while (*(end + 1) && (is_double_quote(end + 1) || is_single_quote(end + 1))) {
        end++;
        if (is_double_quote(end))
            double_string(&end, ctx);
        else
            single_string(&end, ctx);
    }
    
    new = init_token(start, end - start + 1, ctx);
    add_token(new, tokens, current);
    *lexeme = end + 1;
}

