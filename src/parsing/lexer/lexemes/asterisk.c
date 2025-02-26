/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:50:28 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/26 17:18:18 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_asterisk(char *lexeme)
{
	if (lexeme && is_eqlchar(*lexeme, '*'))
		return (true);
	return (false);
}
