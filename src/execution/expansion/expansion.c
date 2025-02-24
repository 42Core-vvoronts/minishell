/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:33:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/24 12:24:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_chunk(char **end, char **result, t_ctx *ctx);
void	single_chunk(char **end, char **result, t_ctx *ctx);
void	plain_chunk(char **end, char **result, t_ctx *ctx);
char	*handle_variable(char **end, t_ctx *ctx);
bool	is_valid_var_char(char *c);
bool	is_literal(char *c);

bool	is_valid_var_char(char *c)
{
	return (ft_isalnum(*c) || is_eqlchar(*c, '_'));
}

bool	is_literal(char *c)
{
	return (!is_single_quote(c) && !is_double_quote(c) && !is_dollar(c));
}

void	ft_strnjoin(char **result, char *str, size_t len, t_ctx *ctx)
{
	char	*tmp;
	char	*mem;
	size_t	res_len;

	tmp = *result;
	res_len = ft_strlen(tmp);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	mem = malloc(res_len + len + 1);
	if (!mem)
		error(-1, ctx, (t_m){strerror(errno)});
	ft_memcpy(mem, tmp, res_len);
	ft_memcpy(mem + res_len, str, len);
	mem[res_len + len] = '\0';
	free(tmp);
	*result = mem;
}

/**
 * @brief Get the value of the variable
 *
 * @param end pointer to the current character of string
 * @param ctx pointer to context of programm to cleanup
 * 
 * @return value of the variable
 * 
 * @note Moves end pointer to the end of the chunk
 */
char	*handle_variable(char **end, t_ctx *ctx)
{
	char	*value;
	char	*varname;
	char	*start;

	(*end)++;
	start = *end;
	while (**end && is_valid_var_char(*end))
		(*end)++;
	if (*end - start == 0)
		value = "$";
	//specific handle of $?
	else
	{
		varname = ft_strndup(start, *end - start);
		if (!varname)
			error(-1, ctx, (t_m){strerror(errno)});
		value = get_val(ctx, varname);
		free (varname);
	}
	return (value);
}

/**
 * @brief Process single quoted chunk of string
 *
 * @param end pointer to the current character of string
 * @param result pointer to the result string
 * @param ctx pointer to context of programm to cleanup
 * 
 * @note Moves end pointer to the end of the chunk, adds chunk to result string
 */
void	single_chunk(char **end, char **result, t_ctx *ctx)
{
	char	*start;

	if (!is_single_quote(*end))
		return ;
	(*end)++;
	while (**end && !is_single_quote(*end))
	{
		if (is_double_quote(*end))
		{
			ft_strnjoin(result, "\"", 1, ctx);
			double_chunk(end, result, ctx);
			ft_strnjoin(result, "\"",1,  ctx);
		}
		else
		{
			start = *end;
			while (**end && (!is_single_quote(*end) || is_double_quote(*end)))
				(*end)++;
			ft_strnjoin(result, start, *end - start, ctx);
		}
	}
	if (is_single_quote(*end))
		(*end)++;
}
/**
 * @brief Process double quoted chunk of string
 *
 * @param end pointer to the current character of string
 * @param result pointer to the result string
 * @param ctx pointer to context of programm to cleanup
 * 
 * @note Moves end pointer to the end of the chunk, adds chunk to result string
 */
void	double_chunk(char **end, char **result, t_ctx *ctx)
{
	char	*value;
	char	*start;

	if (!is_double_quote(*end))
		return ;
	(*end)++;
	while (**end && !is_double_quote(*end))
	{
		if (is_single_quote(*end))
		{
			ft_strnjoin(result, "\'", 1, ctx);
			single_chunk(end, result, ctx);
			ft_strnjoin(result, "\'", 1, ctx);
		}
		else if (is_dollar(*end))
		{
			value = handle_variable(end, ctx);
			ft_strnjoin(result, value, ft_strlen(value), ctx);
		}
		else if (is_double_quote(*end))
		{
			(*end)++;
			return ;
		}
		else
		{
			start = *end;
			while (*end && is_literal(*end))
				(*end)++;
			ft_strnjoin(result, start, *end - start, ctx);
		}
	}
	if (is_double_quote(*end))
		(*end)++;
}

/**
 * @brief Process no quotes chunk of string
 *
 * @param end pointer to the current character of string
 * @param result pointer to the result string
 * @param ctx pointer to context of programm to cleanup
 * 
 * @note Moves end pointer to the end of the chunk, adds chunk to result string
 */
void	plain_chunk(char **end, char **result, t_ctx *ctx)
{
	char	*value;
	char	*start;
	char	*tmp;

	char blank[2] = {5, '\0'};

	while (**end && !is_single_quote(*end) && !is_double_quote(*end))
	{
		if (is_dollar(*end))
		{
			value = handle_variable(end, ctx);
			tmp = value;
			while (*tmp)
			{
				if (is_blank(tmp))
					*tmp = 4;
				tmp++;
			}
			ft_strnjoin(result, value, ft_strlen(value), ctx);
		}
		if (is_asterisk(*end))
		{
			ft_strnjoin(result, blank, 1, ctx);
			while (is_asterisk(*end))
				(*end)++;
		}
		else if (is_literal(*end))
		{
			start = *end;
			while (**end && is_literal(*end) && !is_asterisk(*end))
				(*end)++;
			ft_strnjoin(result, start, *end - start, ctx);
		}
	}	
}

/**
 * @brief Process the ARGUMENT, CONTEN and FILENAME nodes content
 *
 * @param lexeme content of the node
 * @param ctx pointer to context of programm to cleanup
 * 
 * Handle the expansion of variables and preparing wildcard expansion 
 * depending on quotation of string
 * 
 * @return result string with expanded variables and trimmed quotes when nessesary
 */
char	*expand(char **lexeme, t_ctx *ctx)
{
	char	*result;
	char	*end;

	result = malloc(sizeof(char));
	if (!result)
		error(-1, ctx, (t_m){strerror(errno)});
	end = *lexeme;
	*result = '\0';
	while (*end)
	{
		double_chunk(&end, &result, ctx);
		single_chunk(&end, &result, ctx);
		plain_chunk(&end, &result, ctx);
	}
	// free(lexeme);
	// printf("%s", result);
	if (result)
		ft_strnjoin(&result, "\0", 1, ctx);
	return (result);
}

//"ls$USER'LITERAL*'"$USER'aaa'