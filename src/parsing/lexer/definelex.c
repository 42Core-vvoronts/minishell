/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lexemes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 09:57:09 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_single_quote(char *lexeme)
{
	if (is_eqlstr(lexeme, "\'"))
		return true;
	return false;
}

bool is_double_quote(char *lexeme)
{
	if (is_eqlstr(lexeme, "\""))
		return true;
	return false;
}
bool is_open_parenthesis(char *lexeme)
{
	if (is_eqlstr(lexeme, "("))
		return true;
	return false;
}

bool is_close_parenthesis(char *lexeme)
{
	if (is_eqlstr(lexeme, ")"))
		return true;
	return false;
}

bool is_pipe_symbol(char *lexeme)
{
	if (is_eqlstr(lexeme, "|"))
		return true;
	return false;
}

bool is_less(char *lexeme)
{
	if (is_eqlstr(lexeme, "<"))
		return true;
	return false;
}

bool is_greater(char *lexeme)
{
	if (is_eqlstr(lexeme, ">"))
		return true;
	return false;
}

bool is_double_greater(char *lexeme)
{
	if (is_eqlstr(lexeme, ">>"))
		return true;
	return false;
}

bool is_double_less(char *lexeme)
{
	if (is_eqlstr(lexeme, "<<"))
		return true;
	return false;
}

bool is_and(char *lexeme)
{
	if (is_eqlstr(lexeme, "&&"))
		return true;
	return false;
}

bool is_or(char *lexeme)
{
	if (is_eqlstr(lexeme, "||"))
		return true;
	return false;
}
