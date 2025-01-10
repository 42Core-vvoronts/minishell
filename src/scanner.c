/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:05 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 16:54:14 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char	**scan(char *input)
{
	char **lexemes;
	lexemes = ft_split(input, ' ');

	return lexemes;
}