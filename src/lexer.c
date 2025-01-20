/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:42 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/20 12:58:14 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int is_executable(const char *lexeme)
// {
// 	const char *executables[] = {"cat", "ls", "grep"};
// 	size_t i = 0;
	
// 	while (i < sizeof(executables) / sizeof(executables[0]))
// 	{
// 		if (strcmp(lexeme, executables[i]) == 0)
// 		{
// 			return 1;
// 		}
// 		i++;
// 	}
// 	return 0;
// }

// static int is_builtin(const char *lexeme) 
// {
//     const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
//     size_t i = 0;

//     while (i < sizeof(builtins) / sizeof(builtins[0])) 
// 	{
//         if (strcmp(lexeme, builtins[i]) == 0) {
//             return 1; 
//         }
//         i++;
//     }
//     return 0;
// }

t_type label(char *lexeme) 
{
	if (ft_strcmp(lexeme, "&&") == 0) 
		return AND;
	if (ft_strcmp(lexeme, "||") == 0) 
		return OR;
	// LPAR,
	// RPAR,
	if (ft_strcmp(lexeme, "|") == 0) 
		return PIPE;
    if (ft_strcmp(lexeme, "<") == 0)
		return REDIR_IN;
	if (ft_strcmp(lexeme, ">") == 0)
		return REDIR_OUT;
	if (ft_strcmp(lexeme, ">>") == 0)
		return REDIR_APPEND;
	if (ft_strcmp(lexeme, "<<") == 0)
		return REDIR_HEREDOC;
	return WORD;
	// if (ft_strcmp(lexeme, "&&") == 0) return AND;
	// if (ft_strcmp(lexeme, "||") == 0) return OR;
	// if (ft_strcmp(lexeme, "(") == 0) return GROUP_OPEN;
	// if (ft_strcmp(lexeme, "(") == 0) return GROUP_CLOSE;
	// if (ft_strcmp(lexeme, "|") == 0) return PIPE;
    // if ((ft_strcmp(lexeme, "<") == 0) || (ft_strcmp(lexeme, ">") == 0) || (ft_strcmp(lexeme, ">>") == 0))
	// 	return REDIR;
    // if (ft_strcmp(lexeme, "<<") == 0) return HEREDOC;
	// if (ft_strcmp(lexeme, "\"") == 0) return DOUBLE_QUOTE;
	// if (ft_strcmp(lexeme, "'") == 0) return SINGLE_QUOTE;
	// if (lexeme[0] == '$' && lexeme[1] != '\0')
	// 	return VARIABLE;
	// if ((is_builtin(lexeme) || is_executable(lexeme)))
	// 	return COMMAND;	
	// else return ARGUMENT;
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
	printf("\nTokens:\n");
	print_tokens(tokens);

    return tokens;
}
