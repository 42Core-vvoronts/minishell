/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:53:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/06 13:05:21 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char **get_var(t_ctx *ctx, char *varname)
{
	char	**envp;
	int		result;

	envp = ctx->envp;
	while (*envp)
	{
		//fix here
		result = ft_strncmp(*envp, varname, ft_strchr(*envp, '=') - *envp);
		if (result == 0)
			return (envp);
		envp++;
	}
	return (NULL);
}

char *get_val(t_ctx *ctx, char *varname)
{
	char	**var;

	var = get_var(ctx, varname);
	if (var)
		return (*var + (ft_strchr(*var, '=') - *var));
	return (NULL);
}
