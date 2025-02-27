/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 05:53:35 by ipetrov           #+#    #+#             */
/*   Updated: 2025/02/27 10:14:26 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_eqlvar(char *envvar, char *varname)
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

//return pointer to envp variable
//return NULL if not found
//varname = "PATH" or "HOME", no any $ or \n
char	**get_var(t_ctx *ctx, char *varname)
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

//return content of envp variable
//return NULL if variable not found
//varname = "PATH" or "HOME", no any $ or \n
char	*get_val(t_ctx *ctx, char *varname)
{
	char	**var;

	var = get_var(ctx, varname);
	if (var)
		return (*var + (ft_strchr(*var, '=') - *var + 1));
	return (NULL);
}

static	void	add_new(t_node *node, char *var)
{
	size_t	i;
	char	**result;

	i = ft_parrlen(node->ctx->envp);
	result = ft_calloc(i + 2, sizeof(char *));
	if (!result)
		error(-1, node->ctx, (t_m){strerror(errno), NULL});
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

//add variable to envp
//it replaces duplicate or creates new
//it mallocs char *str
void	add_var(t_node *node, char *str)
{
	char	**var;
	char	*dupedstr;

	dupedstr = ft_strdup(str);
	if (!dupedstr)
		error(-1, node->ctx, (t_m){strerror(errno), NULL});
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
