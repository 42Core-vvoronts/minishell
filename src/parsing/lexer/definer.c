/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:56:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 15:18:30 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word_lexeme(char *lexeme)
{
    if (ft_isalpha(*lexeme) || ft_isdigit(*lexeme) || 
        *lexeme == '_' || *lexeme == '-' || *lexeme == '.')
        return true;
    return false;
}

bool is_single_quote(char *lexeme)
{
    if (is_eqlchar(*lexeme, '\''))
        return true;
    return false;
}

bool is_double_quote(char *lexeme)
{
    if (is_eqlchar(*lexeme, '\"'))
        return true;
    return false;
}

bool is_open_parenthesis(char *lexeme)
{
    if (is_eqlchar(*lexeme, '('))
        return true;
    return false;
}

bool is_close_parenthesis(char *lexeme)
{
    if (is_eqlchar(*lexeme, ')'))
        return true;
    return false;
}

bool is_pipe_symbol(char *lexeme)
{
    if (is_eqlchar(*lexeme, '|'))
        return true;
    return false;
}

bool is_less(char *lexeme)
{
    if (is_eqlchar(*lexeme, '<'))
        return true;
    return false;
}

bool is_greater(char *lexeme)
{
    if (is_eqlchar(*lexeme, '>'))
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

bool is_space(char *lexeme)
{
    if (is_eqlchar(*lexeme, ' ') || is_eqlchar(*lexeme, '\t') || is_eqlchar(*lexeme, '\n'))
        return true;
    return false;
}
