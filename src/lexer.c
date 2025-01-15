/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:42 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/15 18:16:37 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_builtin(const char *lexeme) 
{
    const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    size_t i = 0;

    while (i < sizeof(builtins) / sizeof(builtins[0])) 
	{
        if (strcmp(lexeme, builtins[i]) == 0) {
            return 1; 
        }
        i++;
    }
    return 0;
}
e_type label(char *lexeme) 
{
	if (ft_strcmp(lexeme, "(") == 0 || ft_strcmp(lexeme, ")") == 0) return GROUP;
	if (ft_strcmp(lexeme, "&&") == 0) return AND;
	if (ft_strcmp(lexeme, "||") == 0) return OR;
	if (ft_strcmp(lexeme, "|") == 0) return PIPE;
    if (ft_strcmp(lexeme, "<") == 0) return INPUT;
    if (ft_strcmp(lexeme, ">") == 0) return OUTPUT;
    if (ft_strcmp(lexeme, ">>") == 0) return APPEND;
    if (ft_strcmp(lexeme, "<<") == 0) return HEREDOC;
	if ((is_builtin(lexeme)))
		return EXEC;	
	else return WORD;
}

// e_cmd typify(e_label token)
// {
// 	if (token == PIPETOK)
// 		return PIPE;
// 	return EXEC;
// }

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
		newtok->type = label((*lexemes)); 
        // newtok->type = typify(newtok->type); 
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

