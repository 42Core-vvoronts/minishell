/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/09 19:32:08 by vvoronts         ###   ########.fr       */
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

// t_type	typify_quotes(char *lexeme)
// {
// 	if (lexeme[0] == '"' && lexeme[ft_strlen(lexeme) - 1] == '"')
// 		return WORD_DOUBLE_QUOTES;
// 	if (lexeme[0] == '\'' && lexeme[ft_strlen(lexeme) - 1] == '\'')
// 		return WORD_SINGLE_QUOTES;
// 	return WORD_ZERO_QUOTES;
// }

t_type typify(char *lexeme) 
{
	if (is_eqlstr(lexeme, "&&")) 
		return AND;
	if (is_eqlstr(lexeme, "||")) 
		return OR;
	if (is_eqlstr(lexeme, "(") || is_eqlstr(lexeme, ")"))
		return GROUP;
	if (is_eqlstr(lexeme, "|")) 
		return PIPE;
    if (is_eqlstr(lexeme, "<"))
		return REDIR_IN;
	if (is_eqlstr(lexeme, ">"))
		return REDIR_OUT;
	if (is_eqlstr(lexeme, ">>"))
		return REDIR_APPEND;
	if (is_eqlstr(lexeme, "<<"))
		return REDIR_HEREDOC;
	return ARGUMENT;
}

t_tok *lexer(char *cmdline)
{
    t_tok *tokens = NULL;
    t_tok *curtok = NULL;
    t_tok *newtok = NULL;
	char **lexemes;
	
	lexemes = ft_split(cmdline, ' ');
    while (*lexemes)
    {
        // Process current lexeme
        newtok = malloc(sizeof(t_tok));
        newtok->lexeme = *lexemes; 
		newtok->type = typify((*lexemes)); 
        // newtok->type = typify(newtok->type); 
        newtok->next = NULL;

        if (tokens == NULL)
            tokens = newtok; 
        else
            curtok->next = newtok;

        curtok = newtok; 

        lexemes++; 
    }
	// printf("\nTokens:\n");
	// print_tokens(tokens);
    return tokens;
}
