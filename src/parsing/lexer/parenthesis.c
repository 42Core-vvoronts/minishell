/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 19:27:49 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_open_parenthesis(char *lexeme)
{
    if (is_eqlchar(*lexeme, '('))
        return true;
    return false;
}

bool	is_close_parenthesis(char *lexeme)
{
    if (is_eqlchar(*lexeme, ')'))
        return true;
    return false;
}

void	tokenize_parenthesis(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
}
