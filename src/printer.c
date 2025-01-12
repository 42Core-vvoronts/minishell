#include "minishell.h"

const char *get_label_name(e_label label) 
{
    switch (label) {
        case PIPE: return "PIPE";
        case INPUT: return "INPUT";
        case OUTPUT: return "OUTPUT";
        case APPEND: return "APPEND";
        case HEREDOC: return "HEREDOC";
        case LITERAL: return "LITERAL";
        case ENV_VAR: return "ENV_VAR";
        case STATUS_VAR: return "STATUS_VAR";
        case QUOTE_SINGLE: return "QUOTE_SINGLE";
        case QUOTE_DOUBLE: return "QUOTE_DOUBLE";
        case BUILTIN: return "BUILTIN";
        case ASSIGNMENT: return "ASSIGNMENT";
        case PATH: return "PATH";
        case ERROR: return "ERROR";
        case END: return "END";
        default: return "UNKNOWN";
    }
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
