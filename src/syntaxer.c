/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:37:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/13 19:34:25 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"
#include <stdio.h>  // For debugging

#include "minishell.h"
#include <stdio.h>

t_ast *addnode(t_tok *tok)
{
    if (!tok)	
        return NULL;

    t_ast *node = malloc(sizeof(t_ast));

    node->type = tok->type;
    node->tok = tok;
    node->cmd = tok->lexeme;  // Command/Token lexeme ("cat", "|", etc.)
    node->args = NULL;        // Not used in this case
    node->left = NULL;
    node->right = NULL;
    return node;
}

int get_precedence(char op)
{
    if (op == '|') 
        return 1;
    return 0;  // No precedence for non-pipe operators in this example
}

t_ast *create_tree(t_tok **tok, int precedence)
{
    if (!tok || !*tok) 
	{
        return NULL;
    }
    // Create the first node (could be LITERAL or PIPE)
    t_ast *left = addnode(*tok);
    *tok = (*tok)->next;

    // Handle the operators and respect precedence
    while (*tok && get_precedence((*tok)->lexeme[0]) >= precedence) 
	{
        char op = (*tok)->lexeme[0];  // Get the operator

        // Create an operator node
        t_ast *op_node = addnode(*tok);
        *tok = (*tok)->next;

        // Process the right-hand side (recursive call to handle precedence)
        t_ast *right = create_tree(tok, get_precedence(op) + 1);
        if (!right) return NULL;

        // Link the operator node with the left and right children
        op_node->left = left;
        op_node->right = right;
        left = op_node; 
    }

    return left;
}


t_ast *syntax(t_tok *tok)
{
    return create_tree(&tok, 0);
}


// t_ast *addnode(t_tok *tok)
// {
//     if (!tok) {
//         printf("Error: Null token passed to addnode\n");
//         return NULL;
//     }

//     t_ast *node = malloc(sizeof(t_ast));
//     if (!node) {
//         printf("Error: Memory allocation failed\n");
//         return NULL;
//     }

//     node->type = tok->type;
//     node->tok = tok;
//     node->cmd = tok->lexeme;
//     node->args = NULL;
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

// int get_precedence(char op)
// {
//     if (op == '|') 
//         return 1;
//     return 0;
// }

// t_ast *create_tree(t_tok **tok, int precedence)
// {
//     if (!tok || !*tok) {
//         printf("Error: Null token pointer\n");
//         return NULL;
//     }

//     t_ast *left = addnode(*tok);
//     if (!left) return NULL;

//     *tok = (*tok)->next;

//     while (*tok && get_precedence((*tok)->lexeme[0]) >= precedence)
//     {
//         char op = (*tok)->lexeme[0];
//         printf("Processing operator: %c\n", op);
        
//         t_ast *op_node = addnode(*tok);
//         *tok = (*tok)->next;

//         t_ast *right = create_tree(tok, get_precedence(op) + 1);
//         if (!right) return NULL;  // Avoid segmentation if right is null

//         op_node->left = left;
//         op_node->right = right;
//         left = op_node;
//     }

//     return left;
// }

// t_ast *syntax(t_tok *tok)
// {
//     return create_tree(&tok, 0);
// }


