/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:42 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/12 14:59:05 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**scan(char *input)
{
	char **lexemes;
	lexemes = ft_split(input, ' ');

	return lexemes;
}

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	while (*s1 && *s2 && *s1 == *s2)
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)*s1 - (unsigned char)*s2);
// }

e_label label(char *lexeme) 
{
    if (ft_strcmp(lexeme, "|") == 0) return PIPE;
    if (ft_strcmp(lexeme, "<") == 0) return INPUT;
    if (ft_strcmp(lexeme, ">") == 0) return OUTPUT;
    if (ft_strcmp(lexeme, ">>") == 0) return APPEND;
    if (ft_strcmp(lexeme, "<<") == 0) return HEREDOC;
    if (ft_strcmp(lexeme, "$?") == 0) return STATUS_VAR;
    if (lexeme[0] == '$' && ft_isalpha(lexeme[1])) return ENV_VAR;
    if (lexeme[0] == '\'') return QUOTE_SINGLE;
    if (lexeme[0] == '"') return QUOTE_DOUBLE;
    if (ft_isalpha(lexeme[0])) return BUILTIN;
    if (strchr(lexeme, '=') != NULL) return ASSIGNMENT;
    if (strchr(lexeme, '/') != NULL) return PATH;
    if (strlen(lexeme) == 0 || !isprint(lexeme[0])) return ERROR;
    return LITERAL;
}

e_type typify(e_label label)
{
	if (label == LITERAL)
		return WORD;
	return OPERATOR;
}

t_tok *lexer(char **lexemes)
{
    t_tok *tokens = NULL;
    t_tok *curtok = NULL;
    t_tok *newtok = NULL;

    // Process each lexeme in the array
    while (*lexemes)
    {
        // Process current lexeme
        newtok = malloc(sizeof(t_tok));
        newtok->lexeme = *lexemes; 
		newtok->label = label((*lexemes)); 
        newtok->type = typify(newtok->label); 
        newtok->next = NULL;

        if (tokens == NULL)
            tokens = newtok; 
        else
            curtok->next = newtok;

        curtok = newtok; 

        lexemes++; 
    }

    return tokens;
}

