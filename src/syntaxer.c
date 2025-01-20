/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:37:56 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/20 13:08:32 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *addnode(t_tok *tok)
{
    if (!tok)	
        return NULL;

    t_ast *node = malloc(sizeof(t_ast));

    node->type = tok->type;
    node->token = tok->lexeme;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// int get_precedence(e_type type)
// {
// 	if (type == AND || type == OR)
// 		return 0;
// 	if (type == GROUP_OPEN || type == GROUP_CLOSE)
// 		return 1;
// 	if (type == PIPE) 
// 		return 1;
// 	if (type == REDIR || type == HEREDOC)
// 		return 2;
// 	if (type == COMMAND)
// 		return 3;
// 	if (type == ARGUMENT)
// 		return 4;
// 	return 6;
// }

t_ast *create_tree(t_tok **tok)
{
    if (!tok || !*tok)
        return NULL;

    t_tok *current = *tok;
    t_tok *first_pipe = NULL;
    t_tok *prev = NULL;

    // Find the first PIPE in the list
    while (current)
    {
        if (current->type == PIPE)
        {
            first_pipe = current;
            break;
        }
        prev = current;
        current = current->next;
    }

    // Base case: no PIPE found, build a subtree for a single command and its arguments
    if (!first_pipe)
    {
        t_ast *cmd_node = NULL;
        t_ast *arg_node = NULL;

        // First token is the command
        cmd_node = malloc(sizeof(t_ast));
        if (!cmd_node)
            return NULL; // Allocation failed
        cmd_node->type = (*tok)->type;
        cmd_node->token = strdup((*tok)->lexeme);
        cmd_node->left = NULL;
        cmd_node->right = NULL;

        *tok = (*tok)->next; // Advance to arguments

        // Attach arguments as a right chain
        t_ast *current_arg = cmd_node;
        while (*tok && ((*tok)->type == WORD || (*tok)->type == REDIR_IN || (*tok)->type == REDIR_OUT || (*tok)->type == REDIR_APPEND || (*tok)->type == REDIR_HEREDOC))
        {
            arg_node = malloc(sizeof(t_ast));
            if (!arg_node)
                return NULL; // Allocation failed
            arg_node->type = (*tok)->type;
            arg_node->token = strdup((*tok)->lexeme);
            arg_node->left = NULL;
            arg_node->right = NULL;

            current_arg->right = arg_node;
            current_arg = arg_node;
            *tok = (*tok)->next; // Advance token list
        }

        return cmd_node;
    }

    // Create the root node for the current PIPE
    t_ast *root = malloc(sizeof(t_ast));
    if (!root)
        return NULL; // Allocation failed
    root->type = first_pipe->type;
    root->token = strdup(first_pipe->lexeme);
    root->left = NULL;
    root->right = NULL;

    // Split the token list at the first PIPE
    current = *tok;
    while (current != first_pipe)
    {
        prev = current;
        current = current->next;
    }
    if (prev)
        prev->next = NULL; // Break the list

    // Recursively build left and right subtrees
    root->left = create_tree(tok);
    root->right = create_tree(&(first_pipe->next));

    return root;
}

// backwards tree
// t_ast *create_tree(t_tok **tok)
// {
//     if (!tok || !*tok)
//         return NULL;

//     t_tok *current = *tok;
//     t_tok *last_pipe = NULL;
//     t_tok *prev = NULL;

//     // Find the last PIPE in the list
//     while (current)
//     {
//         if (current->type == PIPE)
//             last_pipe = current;
//         prev = current;
//         current = current->next;
//     }

//     // Base case: no PIPE found, build a subtree for a single command and its arguments
//     if (!last_pipe)
//     {
//         t_ast *cmd_node = NULL;
//         t_ast *arg_node = NULL;

//         // First token is the command
//         cmd_node = malloc(sizeof(t_ast));
//         if (!cmd_node)
//             return NULL; // Allocation failed
//         cmd_node->type = (*tok)->type;
//         cmd_node->token = strdup((*tok)->lexeme);
//         cmd_node->left = NULL;
//         cmd_node->right = NULL;

//         *tok = (*tok)->next; // Advance to arguments

//         // Attach arguments as a right chain
//         t_ast *current_arg = cmd_node;
//         while (*tok && (*tok)->type == WORD)
//         {
//             arg_node = malloc(sizeof(t_ast));
//             if (!arg_node)
//                 return NULL; // Allocation failed
//             arg_node->type = (*tok)->type;
//             arg_node->token = strdup((*tok)->lexeme);
//             arg_node->left = NULL;
//             arg_node->right = NULL;

//             current_arg->right = arg_node;
//             current_arg = arg_node;
//             *tok = (*tok)->next; // Advance token list
//         }

//         return cmd_node;
//     }

//     // Create the root node for the current PIPE
//     t_ast *root = malloc(sizeof(t_ast));
//     if (!root)
//         return NULL; // Allocation failed
//     root->type = last_pipe->type;
//     root->token = strdup(last_pipe->lexeme);
//     root->left = NULL;
//     root->right = NULL;

//     // Split the token list at the last PIPE
//     current = *tok;
//     while (current != last_pipe)
//     {
//         prev = current;
//         current = current->next;
//     }
//     if (prev)
//         prev->next = NULL; // Break the list

//     // Recursively build left and right subtrees
//     root->left = create_tree(tok);
//     root->right = create_tree(&(last_pipe->next));

//     return root;
// }

	//search last pipe
	// everything after last pipe goes to the right 
		// prev | <- left | right -> cmd4
		// NULL <- left cmd4 right -> arg4
		// NULL <- left arg4 right -> NULL
	// everything before last pipe goes to the left
	// coninue for all pipes backwards
// }


// t_ast *create_tree(t_tok **tok, int precedence)
// {
//     if (!tok || !*tok) return NULL;

//     t_ast *left = addnode(*tok);
//     *tok = (*tok)->next;

//     while (*tok && get_precedence((*tok)->type) >= precedence) 
//     {
//         t_type op_type = (*tok)->type;  // Get the operator type
//         t_ast *op_node = addnode(*tok);
//         *tok = (*tok)->next;

//         // Recursively process the right-hand side to respect precedence
//         t_ast *right = create_tree(tok, get_precedence(op_type) + 1);
//         if (!right) return NULL;

//         // Link the operator node with left and right children
//         op_node->left = left;
//         op_node->right = right;
//         left = op_node; 
//     }

//     return left;
// }

t_ast *syntax(t_tok *tok)
{
	// check_syntax();
    return create_tree(&tok);
}


