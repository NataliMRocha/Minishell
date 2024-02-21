
#include "../../includes/minishell.h"
t_ast	*ast_constructor(t_token *tokens);
#include <stdio.h>
#include <stdlib.h>

t_token	*search_and_or(t_token *tokens)
{
	t_token	*temp;

	temp = find_last_node(tokens);
	while (temp)
	{
		if (temp->type == AND || temp->type == OR)
			return (temp);
		temp = temp->prev;
	}
	return (NULL);
}

t_token	*search_pipe(t_token *tokens)
{
	t_token	*temp;

	temp = find_last_node(tokens);
	while (temp)
	{
		if (temp->type == PIPE)
			return (temp);
		temp = temp->prev;
	}
	return (NULL);
}

t_token	*search_redir(t_token *tokens)
{
	t_token	*temp;

	temp = find_last_node(tokens);
	while (temp)
	{
		if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND
			|| temp->type == REDIR_IN || temp->type == HEREDOC)
			return (temp);
		temp = temp->prev;
	}
	return (NULL);
}

t_token	*split_tokens(t_token *tokens, t_token *token_to_split)
{
	t_token	*right;

	right = token_to_split->next;
	right->prev = NULL;
	return (right);
}

int	ast_split_node(t_ast *root, t_token *tokens, t_token *token_to_split)
{
	t_token	*right;

	right = NULL;
	if (!root || !tokens || !token_to_split)
		return (0);
	right = split_tokens(tokens, token_to_split);
	root->type = token_to_split->type;
	tokens = token_to_split->prev;
	tokens->next = NULL;
	root->left = ast_constructor(tokens);
	root->right = ast_constructor(right);
	return (1);
}

void	try_split_else_exec(t_ast *ast_node, t_token *tokens)
{
	if (ast_split_node(ast_node, tokens, search_and_or(tokens)))
		return ;
	if (ast_split_node(ast_node, tokens, search_pipe(tokens)))
		return ;
	if (ast_split_node(ast_node, tokens, search_redir(tokens)))
		return ;
	ast_node->type = EXEC;
	ast_node->tokens_to_exec = tokens;
}

t_ast	*ast_constructor(t_token *tokens)
{
	t_ast		*root;

	root = ft_calloc(1, sizeof(t_ast));
	try_split_else_exec(root, tokens);
	return (root);
}

// TODO: apagar essas funções

void	print_ast(t_ast *root)
{
	if (root)
	{
		print_ast(root->left);
		if (root && root->tokens_to_exec)
			printf("%s ", root->tokens_to_exec->data);
		else
			printf("%d ", root->type);
		print_ast(root->right);
	}
}

int	main(void)
{
	t_ast	*root;
	t_token	*tokens;

	tokens = NULL;
	list_fill(&tokens, "false || cmd1 | cmd2 && cmd3 | cmd4", NULL);
	root = ast_constructor(tokens);
	print_ast(root);
	printf("\n\n");
	return (0);
}
