/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:09:27 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 17:33:54 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char *lexeme)
{
	if (is_pipe_symbol(lexeme) || is_less(lexeme) || is_greater(lexeme) || 
	is_and(lexeme) || is_open_parenthesis(lexeme) || is_close_parenthesis(lexeme))
		return true;
	return false;
}

void	skip_spaces(char **statement)
{
	while (is_space(*statement))
		(*statement)++;
}

void	handle_quotes(char **statement, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (!*statement)
		error_exit("end of statement");
	if (!is_double_quote(*statement) && !is_single_quote(*statement))
		return ;
	start = *statement;
	end = *statement + 1;
	if (*end == '\0')
		error_exit("end of statement");
	while (*end && !is_double_quote(end) && !is_single_quote(end))
		end++;
	if (!is_double_quote(end) && !is_single_quote(end))
		error_exit("Unclosed quote");
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*statement = end + 1;
}

void	handle_words(char **statement, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (!*statement)
		error_exit("end of statement");
	if (!is_word_lexeme(*statement))
		return ;
	start = *statement;
	end = start;
	while (*end && is_word_lexeme(end))
		end++;
	new = init_token(start, end - start);
	add_token(new, tokens, current);
	*statement = end;
	}
	
void	handle_operators(char **statement, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (!*statement)
		error_exit("end of statement");
	if (!is_operator(*statement))
		return ;
	start = *statement;
	end = start;

	if (is_open_parenthesis(end) || is_close_parenthesis(end))
	{
		new = init_token(start, end - start + 1);
		add_token(new, tokens, current);
		*statement = end + 1;
		return ;
	}
	if (is_double_greater(start) || is_double_less(start))
		end++;
	if (*end == '\0')
		error_exit("end of statement");
	new = init_token(start, end - start);
	add_token(new, tokens, current);
	*statement = end;
}
