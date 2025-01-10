/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:34 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 14:08:19 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./minishel \"expression\"\n");
		return 1;
	}
	parsing(argv[1]);
	
	return 0;
}