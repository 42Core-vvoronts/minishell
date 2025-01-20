/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:14:59 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/20 19:21:29 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "constants.h"
# include "../lib/elibft/include/elibft.h"

# include <ctype.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <string.h>    // strlen
# include <stdlib.h>    // exit
# include <unistd.h>    // syscalls
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_ctx
{
	char **envp;
	char *ttyname;
	char **argv;
	pid_t last_child;
} t_ctx;

// -- INIT --

// -- PROMPT --

// -- PARSING --
t_ast	*parsing(char *input);
// Lexer
t_tok *lexer(char *cmdline);
// e_cmd typify(e_label label);
t_type label(char *lexeme);
bool is_not_space(char symbol);
// Syntaxer
t_ast *syntax(t_tok *tok);
t_ast *create_tree(t_tok **tok);
t_ast *addnode(t_tok *tok);

// -- EXPANSION --

// -- ENVAR --

// -- EXECUTION --

// -- SIGNALS --

// -- ERROR --


//execution
int run_cmd(t_ctx *ctx, char **argv);
char *get_validpath(t_ctx *ctx, char **argv);
char *get_varvalue(t_ctx *ctx, char *varname);

//redirection
int	redir_in(char *pathname);

//error
void error(t_ctx *ctx, t_error error);

// DELETE
void print_tokens(t_tok *tokens);
void print_ast(t_ast *ast, int depth);

#endif
