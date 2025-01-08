/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 16:59:50 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include "structs.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>

int parsing(char *input);
void print_tokens(t_tok *tokens);
void print_ast(t_ast *ast, int depth);
t_ast *parse(t_tok *tok);
t_ast *create_tree(t_tok **tok, int precedence);

char **scan(char *input);
t_tok *lexer(char **lexemes);

e_type typify(e_label label);
e_label label(char lexeme);
bool is_not_space(char symbol);


#endif
