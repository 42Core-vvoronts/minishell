/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:42 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/13 18:56:46 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

e_label label(char *lexeme) 
{
	if (ft_strlen(lexeme) == 1 && ft_strcmp(lexeme, "|") == 0) return PIPETOK;
	else return LITERAL;
	
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

e_cmd typify(e_label token)
{
	if (token == PIPETOK)
		return PIPE;
	return EXEC;
}

t_tok *lexer(char *cmdline)
{
    t_tok *tokens = NULL;
    t_tok *curtok = NULL;
    t_tok *newtok = NULL;
	char **lexemes;
	
	lexemes = ft_split(cmdline, ' ');
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

