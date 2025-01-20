#include "minishell.h"

const char *get_name(t_type cmd) 
{
	switch (cmd) 
	{
		case AND:
			return "AND";
		case OR:
			return "OR";
		case LPAR:
			return "LPAR";
		case RPAR:
			return "RPAR";
		case PIPE:
			return "PIPE";
		case WORD:
			return "WORD";
		case REDIR_IN:
			return "REDIR_IN";
		case REDIR_OUT:
			return "REDIR_OUT";
		case REDIR_APPEND:
			return "REDIR_APPEND";
		case REDIR_HEREDOC:
			return "REDIR_HEREDOC";
	}
	// switch (cmd) 
	// {
	// 	case GROUP_OPEN:
	// 		return "GROUP_OPEN";
	// 	case GROUP_CLOSE:
	// 		return "GROUP_CLOSE";
	// 	case AND:
	// 		return "AND";
	// 	case OR:
	// 		return "OR";
	// 	case PIPE:
	// 		return "PIPE";
	// 	case REDIR:
	// 		return "REDIR";
	// 	case HEREDOC:
	// 		return "HEREDOC";
	// 	case COMMAND:
	// 		return "COMMAND";
	// 	case ARGUMENT:
	// 		return "ARGUMENT";
	// 	case DOUBLE_QUOTE:
	// 		return "DOUBLE_QUOTE";
	// 	case SINGLE_QUOTE:	
	// 		return "SINGLE_QUOTE";
	// 	case VARIABLE:
	// 		return "VARIABLE";
	// }
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


void print_ast(t_ast *node, int depth)
{
    if (node == NULL)
        return;

    // Indentation for visual hierarchy
    for (int i = 0; i < depth; i++)
    {
        printf("├   ");
    }

    // Print the node type and associated token
    printf("├── %s ", get_name(node->type));
	printf("<%s>\n", node->token);

    // Recursively print left and right children with increased indentation
    print_ast(node->right, depth + 1);
    print_ast(node->left, depth + 1);
}

