/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:11:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/10 19:11:59 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_space(char *lexeme)
{
    if (is_eqlchar(*lexeme, ' ') || is_eqlchar(*lexeme, '\t') || is_eqlchar(*lexeme, '\n'))
        return true;
    return false;
}

void	skip_spaces(char **lexeme)
{
	while (is_space(*lexeme))
		(*lexeme)++;
}


