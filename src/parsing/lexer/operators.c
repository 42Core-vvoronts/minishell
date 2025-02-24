/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:30:20 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/24 15:23:53 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char *lexeme)
{
	if (is_greater(lexeme) || is_less(lexeme) ||
		 is_vertical_bar(lexeme) || is_ampersand(lexeme) ||
		 is_open_parenthesis(lexeme) || is_close_parenthesis(lexeme))
		return true;
	return false;
}

/**
 * @brief Defines which fucntion to use for the operators
 *
 * @param lexeme Start character of lexeme
 * @param tokens The head of the token list
 * @param current The current last node of the token list
 *
 * @note The tokenization itself is done in the helper functions
 * 
 */
void	tokenize_operators(char **lexeme, t_tok **tokens, t_tok **current, t_ctx *ctx)
{
	if (!*lexeme)
		return ;
	if (is_open_parenthesis(*lexeme) || is_close_parenthesis(*lexeme))
		tokenize_parenthesis(lexeme, tokens, current, ctx);
	else if (is_less(*lexeme))
	{
		if (*(*lexeme + 1) && is_less(*lexeme + 1))
			tokenize_heredoc(lexeme, tokens, current, ctx);
		else
			tokenize_angles(lexeme, tokens, current, ctx);
	}
	else if (is_greater(*lexeme))
		tokenize_angles(lexeme, tokens, current, ctx);
	else if (is_vertical_bar(*lexeme))
		tokenize_vertical_bar(lexeme, tokens, current, ctx);
	else if (is_ampersand(*lexeme))
		tokenize_ampersand(lexeme, tokens, current, ctx);
}
