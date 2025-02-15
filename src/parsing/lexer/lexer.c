/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:07:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/12 17:07:51 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief tokenizes the statement and check lexemes validity
 *
 * @param statement initial string of lexemes
 * 
 * Fucntion goes through the statement and uses helper fucntions for each type of character
 * 
 * @return pointer on the list of lexicaly valid tokens
 */
t_tok *lexer(char *statement, t_ctx *ctx)
{
	t_tok *tokens;
	t_tok *current;

	tokens = NULL;
	current = NULL;
    while (statement && *statement)
    {
		skip_blanks(&statement);
		tokenize_quotes(&statement, &tokens, &current, ctx);
		tokenize_words(&statement, &tokens, &current, ctx);
		tokenize_operators(&statement, &tokens, &current, ctx);
    }
    return tokens;
}
