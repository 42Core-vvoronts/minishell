/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:30:20 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/28 14:22:24 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char *lexeme)
{
	if (is_greater(lexeme) || is_less(lexeme)
		|| is_vertical_bar(lexeme) || is_open_parenthesis(lexeme)
		|| is_close_parenthesis(lexeme) || is_double_ampersand(lexeme))
		return (true);
	return (false);
}

/**
 * @brief Defines which fucntion to use for the operators
 *
 * @param lexeme Start character of lexeme
 * @param tok The head of the token list
 * @param cur The current last node of the token list
 *
 * @note The tokenization itself is done in the helper functions
 * 
 */
void	tokenize_operators(char **lexeme, t_tok **tok, t_tok **cur, t_ctx *ctx)
{
	if (ctx->errlex == true || !*lexeme)
		return ;
	if (is_open_parenthesis(*lexeme) || is_close_parenthesis(*lexeme))
		tokenize_parenthesis(lexeme, tok, cur, ctx);
	else if (is_less(*lexeme))
	{
		if (*(*lexeme + 1) && is_less(*lexeme + 1))
			tokenize_heredoc(lexeme, tok, cur, ctx);
		else
			tokenize_angles(lexeme, tok, cur, ctx);
	}
	else if (is_greater(*lexeme))
		tokenize_angles(lexeme, tok, cur, ctx);
	else if (is_vertical_bar(*lexeme))
		tokenize_vertical_bar(lexeme, tok, cur, ctx);
	else if (is_ampersand(*lexeme))
		tokenize_ampersand(lexeme, tok, cur, ctx);
}
