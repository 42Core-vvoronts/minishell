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
		case REDIR:
			return "REDIR";
		case HEREDOC:
			return "HEREDOC";
		case COMMAND:
			return "COMMAND";
		case ARGUMENT:
			return "ARGUMENT";
		case DOUBLE_QUOTE:
			return "DOUBLE_QUOTE";
		case SINGLE_QUOTE:	
			return "SINGLE_QUOTE";
		case VARIABLE:
			return "VARIABLE";
	}
	return "UNDEFINED";
}


void print_tokens(t_tok *token)
{
	while (token)
	{
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

