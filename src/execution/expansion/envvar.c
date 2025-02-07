/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:53:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/07 08:11:47 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static	bool	is_eqlvar(char *envvar, char *varname)
{
	while ((*envvar || *varname) && *envvar != '=')
	{
		if (*envvar != *varname)
			return (false);
		envvar++;
		varname++;
	}
	return (true);
}

char **get_var(t_ctx *ctx, char *varname)
{
	char	**envp;

	envp = ctx->envp;
	while (*envp)
	{
		if (is_eqlvar(*envp, varname))
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

static	void	add_new(t_node *node, char *var)
{
	size_t	i;
	char **result;

	i = ft_parrlen(node->ctx->envp);
	result = ft_calloc(i + 2, sizeof(char *));
	if (!result)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	i = 0;
	while (node->ctx->envp && (node->ctx->envp)[i])
	{
		result[i] = (node->ctx->envp)[i];
		i++;
	}
	result[i] = var;
	free(node->ctx->envp);
	node->ctx->envp = result;
}

void	add_var(t_node *node, char *str)
{
	char **var;
	char *dupedstr;

	dupedstr = ft_strdup(str);
	if (!dupedstr)
		error(node, STRUCT_NODE, MALLOC_FAIL, true);
	var = get_var(node->ctx, str);
	if (var)
	{
		free(*var);
		*var = dupedstr;
	}
	else
	{
		add_new(node, dupedstr);
	}
}
