/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/15 18:04:22 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "constants.h"
# include "libft.h"
# include "ft_printf.h"

# include <ctype.h>
# include <string.h>
# include <stdbool.h>
# include <string.h>    // strlen
# include <stdlib.h>    // exit
# include <unistd.h>    // syscalls
# include <readline/readline.h>
# include <readline/history.h>

int parsing(char *input);

// Lexer
t_tok *lexer(char *cmdline);
// e_cmd typify(e_label label);
e_type label(char *lexeme);
bool is_not_space(char symbol);
// Syntaxer
t_ast *syntax(t_tok *tok);
t_ast *create_tree(t_tok **tok, int precedence);
t_ast *addnode(t_tok *tok);



// Supply, to delete later
void print_tokens(t_tok *tokens);
void print_ast(t_ast *ast, int depth);

#endif
