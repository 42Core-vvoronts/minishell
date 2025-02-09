/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/09 12:40:42 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
