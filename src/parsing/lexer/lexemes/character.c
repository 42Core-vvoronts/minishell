/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:38:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 19:46:15 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_character(char *lexeme)
{
	if (!is_ampersand(lexeme) && !is_vertical_bar(lexeme) && !is_less(lexeme) && !is_greater(lexeme) &&
		!is_open_parenthesis(lexeme) && !is_close_parenthesis(lexeme) && !is_single_quote(lexeme) &&
		!is_double_quote(lexeme) && !is_blank(lexeme) && !is_operator(lexeme))		
		return true;
	return false;
}
