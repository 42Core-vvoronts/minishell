/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 17:12:12 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_character(char *lexeme)
{
	if (!is_double_ampersand(lexeme) && !is_vertical_bar(lexeme) && !is_less(lexeme) && !is_greater(lexeme) &&
		!is_open_parenthesis(lexeme) && !is_close_parenthesis(lexeme) && !is_single_quote(lexeme) &&
		!is_double_quote(lexeme) && !is_blank(lexeme) && !is_operator(lexeme))		
		return (true);
	return (false);
}

bool	is_word_lexeme(char *lexeme)
{
    if (lexeme && (ft_isalpha(*lexeme) || ft_isdigit(*lexeme) || is_eqlchar(*lexeme, '_') ||
		is_character(lexeme)))
        return (true);
    return (false);
}
