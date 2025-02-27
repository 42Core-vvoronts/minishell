/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:24 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/27 15:19:53 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_single_quote(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '\''))
		return (true);
	return (false);
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
	if (is_single_quote(*end))
		(*end)++;
	else
	{
		error(2, ctx, (t_m){"Expected", "\'"});
		ctx->errlex = true;
	}
}

void	double_string(char **end, t_ctx *ctx)
{
	while (**end && !is_double_quote(*end))
		(*end)++;
	if (is_double_quote(*end))
		(*end)++;
	else
	{
		error(2, ctx, (t_m){"Expected", "\""});
		ctx->errlex = true;
	}
}

/**
 * @brief Tokenizes the string in quotes
 *
 * @param lexeme The start character of the lexeme
 * @param tokens The head of the token list
 * @param current The current last node of the token list
 * @param ctx The context
 * 
 * Quoted words need to be splited with space
 * "ls""-la" one token
 * "ls" "-la" two tokens
 * "ls">file.txt two tokens
 * 
 * @note init token and add it to the end of the list
 * 
 */
void	tokenize_quotes(char **end, t_ctx *ctx)
{
    if (!*end || (!is_double_quote(*end) && !is_single_quote(*end)))
        return ;
    while (*end && (is_double_quote(*end) || is_single_quote(*end)))
	{
		(*end)++;
		if (is_double_quote(*end - 1))
		{
			double_string(end, ctx);
			if (ctx->errlex)
				return ;
		}
        else
		{
			single_string(end, ctx);
			if (ctx->errlex)
				return ;	
		}	
    }
}
