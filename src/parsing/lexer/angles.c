/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:01 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 19:33:08 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	tokenize_angles(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (is_less(end))
		;
	else if (is_greater(end + 1))
		end++;
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
		error_exit("syntax error near unexpected token");
}

void	tokenize_heredoc(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
		error_exit("syntax error near unexpected token");
}
