#include "minishell.h"

const char *get_label_name(e_label label) 
{
    switch (label) {
        case PIPETOK: return "PIPE";
        case LITERAL: return "LITERAL";
        default: return "UNKNOWN";
    }
}

const char *get_cmd_name(e_cmd cmd) 
{
	switch (cmd) {
		case EXEC: return "EXEC";
		case REDIRECTION: return "REDIRECTION";
		case PIPE: return "PIPE";
		default: return "UNKNOWN";
	}
}

void print_tokens(t_tok *tokens)
{
	while (tokens)
	{
		// if (tokens->type == WORD)
		// 	printf("Word: %s\n", tokens->lexeme);
		// else if (tokens->type == OPERATOR)
		// 	printf("Operator: %s\n", tokens->lexeme);
		printf("%s: %s\n", get_label_name(tokens->label), tokens->lexeme);

		tokens = tokens->next;
	}
}

void print_ast(t_ast *ast, int depth) 
{
    if (!ast) 
        return;

    for (int i = 0; i < depth; i++) 
    {
        printf("  ");
    }

    if (ast->tok) 
    {
        printf("Node %d - Type: %s, Cmd: %s, args: %s\n", depth, get_cmd_name(ast->type), ast->cmd, ast->args);
    } 
    else 
    {
        printf("Node (Label: NULL)\n");
    }

    // Recursively print left and right subtrees
    print_ast(ast->left, depth + 1);
    print_ast(ast->right, depth + 1);
}

