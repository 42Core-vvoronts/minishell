/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:37:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/08 19:27:07 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

t_ast *addnode(char operator, e_label label)
{
	t_ast *result = malloc(sizeof(t_ast));
	result->label = label;
	result->operator = operator;
	result->left = NULL;
	result->right = NULL;
	return result;
}

int get_precedence(char op)
{
    if (op == '+' || op == '-') 
		return 1;
    if (op == '*' || op == '/') 
		return 2;
    return 0;
}

t_ast *create_tree(t_tok **tok, int precedence)
{
    t_ast *left = NULL;

    // Base case: Parse a single operand (WORD)
    if (*tok && (*tok)->type == WORD) {
        left = addnode((*tok)->label, (*tok)->lexeme[0]); // Create a leaf node
        *tok = (*tok)->next;
    }

    // Loop while the current token is an OPERATOR with sufficient precedence
    while (*tok && (*tok)->type == OPERATOR && get_precedence((*tok)->lexeme[0]) >= precedence) {
        char op = (*tok)->lexeme[0]; // Get the operator
        e_label op_label = (*tok)->label; // Get the operator's label
        *tok = (*tok)->next;

        // Parse the right-hand side with higher precedence
        t_ast *right = create_tree(tok, get_precedence(op) + 1);

        // Create a new node for the operator and attach operands
        t_ast *node = addnode(op_label, op); // Operator node
        node->left = left;
        node->right = right;

        left = node; // Update left to the new subtree
    }

    return left; // Return the constructed subtree
}

	

t_ast *parse(t_tok *tok)
{
    return create_tree(&tok, 0);
}

