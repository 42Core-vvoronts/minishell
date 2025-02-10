/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:09:27 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 18:51:35 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char *lexeme)
{
	if (is_vertical_bar(lexeme) || is_less(lexeme) || is_greater(lexeme) || 
	is_ampersand(lexeme) || is_open_parenthesis(lexeme) || is_close_parenthesis(lexeme))
		return true;
	return false;
}

void	skip_spaces(char **lexeme)
{
	while (is_space(*lexeme))
		(*lexeme)++;
}

void	handle_quotes(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	if (!*lexeme)
		error_exit("end of statement");
	if (!is_double_quote(*lexeme) && !is_single_quote(*lexeme))
		return ;
	start = *lexeme;
	end = *lexeme + 1;
	if (*end == '\0')
		error_exit("end of statement");
	while (*end && !is_double_quote(end) && !is_single_quote(end))
		end++;
	if (!is_double_quote(end) && !is_single_quote(end))
		error_exit("Unclosed quote");
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
}

void	handle_words(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (!*lexeme)
		error_exit("end of statement");
	if (!is_word_lexeme(*lexeme))
		return ;
	start = *lexeme;
	end = start;
	while (*end && is_word_lexeme(end))
		end++;
	new = init_token(start, end - start);
	add_token(new, tokens, current);
	*lexeme = end;
}

void	handle_parenthesis(char **lexeme, t_tok **tokens, t_tok **current)
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

void	handle_greater(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (is_greater(end + 1))
		end++;
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
		error_exit("syntax error near unexpected token");
}

	
void	handle_less(char **lexeme, t_tok **tokens, t_tok **current)
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
	if (is_operator(*lexeme))
		error_exit("syntax error near unexpected token");
}

void	handle_ampersand(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (!is_ampersand(end + 1))
		error_exit("dont need handle &");
	end++;
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
		error_exit("syntax error near unexpected token");
}

void	handle_vertical_bar(char **lexeme, t_tok **tokens, t_tok **current)
{
	char	*start;
	char	*end;
	t_tok	*new;

	start = *lexeme;
	end = start;
	new = NULL;
	if (is_vertical_bar(end + 1))
		end++;
	new = init_token(start, end - start + 1);
	add_token(new, tokens, current);
	*lexeme = end + 1;
	if (is_operator(*lexeme))
		error_exit("syntax error near unexpected token");
}

void	handle_heredoc(char **lexeme, t_tok **tokens, t_tok **current)
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
	
void	handle_operators(char **lexeme, t_tok **tokens, t_tok **current)
{
	if (!*lexeme)
		error_exit("end of statement");
	if (!is_operator(*lexeme))
		return ;
	if (is_open_parenthesis(*lexeme) || is_close_parenthesis(*lexeme))
		handle_parenthesis(lexeme, tokens, current);
	else if (is_greater(*lexeme))
		handle_greater(lexeme, tokens, current);
	else if (is_less(*lexeme))
	{
		if (is_less(*(lexeme + 1)))
			handle_heredoc(lexeme, tokens, current);
		handle_less(lexeme, tokens, current);
	}
	if (is_vertical_bar(*lexeme))
		handle_vertical_bar(lexeme, tokens, current);
	if (is_ampersand(*lexeme))
		handle_ampersand(lexeme, tokens, current);
}
