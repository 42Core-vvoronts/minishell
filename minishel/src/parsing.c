/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:06:02 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 16:59:00 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

const char *get_label_name(e_label label) {
    switch (label) {
        case SPACE: return "SPACE";
        case MATH: return "MATH";
        case COMMAND: return "COMMAND";
        case LITERAL: return "LITERAL";
        case ARGUMENT: return "ARGUMENT";
        case PIPE: return "PIPE";
        case REDIRECTION: return "REDIRECTION";
        default: return "UNKNOWN";
    }
}


int parsing(char *input)
{
	t_tok *tokens;
	char **lexemes;
	t_ast *ast;

	lexemes = scan(input);
	tokens = lexer(lexemes);
	ast = parse(tokens);
	
	printf("\nTokens:\n");
	print_tokens(tokens);
	printf("\nAbstract Syntax Tree:\n");
	print_ast(ast, 0);


	// Clean up
	t_tok *temp;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}

	return 0;
}

void print_tokens(t_tok *tokens)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			printf("Word: %s\n", tokens->lexeme);
		else if (tokens->type == OPERATOR)
			printf("Operator: %s\n", tokens->lexeme);

		tokens = tokens->next;
	}
}
// void print_ast(t_ast *ast, int depth) 
// {
//     if (!ast) return;
//     // Indent to show tree structure
//     for (int i = 0; i < depth; i++) {
//         printf("  ");
//     }
// 	// Print node label and operator
// 	printf("%c\n", ast->operator);

//     // Recursively print left and right subtrees
//     print_ast(ast->left, depth + 1);
//     print_ast(ast->right, depth + 1);
// }

void print_ast(t_ast *ast, int depth) 
{
    if (!ast) 
        return;

    // Indent to show tree structure
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Print node details only if the operator or value is valid
    if (ast->operator != 0) {
        printf("Value: %c Label: %s\n", ast->operator, get_label_name(ast->label));
    } else {
        printf("Node (Label:%s\n", get_label_name(ast->label));
    }

    // Recursively print left and right subtrees
    print_ast(ast->left, depth + 1);
    print_ast(ast->right, depth + 1);
}
