#include "minishell.h"


const char *get_name(e_type cmd) 
{
	switch (cmd) 
	{
		case GROUP:
			return "GROUP";
		case AND:
			return "AND";
		case OR:
			return "OR";
		case PIPE:
			return "PIPE";
		case INPUT:
			return "INPUT";
		case OUTPUT:
			return "OUTPUT";
		case APPEND:
			return "APPEND";
		case HEREDOC:
			return "HEREDOC";
		case EXEC:
			return "EXEC";
		case WORD:
			return "WORD";
	}
	return "UNDEFINED";
}

void print_tokens(t_tok *token)
{
	while (token)
	{
		// if (tokens->type == WORD)
		// 	printf("Word: %s\n", tokens->lexeme);
		// else if (tokens->type == OPERATOR)
		// 	printf("Operator: %s\n", tokens->lexeme);
		printf("%s: %s\n", get_name(token->type), token->lexeme);

		token = token->next;
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
        printf("Node %d - Type: %s, Cmd: %s, args: %s\n", depth, get_name(ast->type), ast->cmd, ast->args);
    } 
    else 
    {
        printf("Node (Label: NULL)\n");
    }

    // Recursively print left and right subtrees
    print_ast(ast->left, depth + 1);
    print_ast(ast->right, depth + 1);
}

