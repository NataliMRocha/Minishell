
#include "../../includes/minishell.h"

t_token	*search_type_to_split(t_token *tokens)
{
	t_token	*temp;

	temp = find_last_node(tokens);
	while (temp && (temp->type != AND && temp->type != OR))
		temp = temp->prev;
	if (temp && (temp->type == AND || temp->type == OR))
		return (temp);
	temp = find_last_node(tokens);
	while (temp && temp->type != PIPE)
		temp = temp->prev;
	if (temp && temp->type == PIPE)
		return (temp);
	temp = find_last_node(tokens);
	while (temp && !is_redirect(temp))
		temp = temp->prev;
	if (temp && is_redirect(temp))
		return (temp);
	return (NULL);
}

int	ast_split_node(t_ast *root, t_token *tokens, t_token *token_to_split)
{
	t_token	*right;

	right = NULL;
	if (!root || !tokens || !token_to_split)
		return (0);
	right = token_to_split->next;
	right->prev = NULL;
	root->type = token_to_split->type;
	tokens = token_to_split->prev;
	if (tokens)
		tokens->next = NULL;
	root->left = ast_constructor(tokens);
	root->right = ast_constructor(right);
	return (1);
}

char	**command_constructor(t_token *tokens)
{
	char	**cmd;
	t_token	*temp;
	int		i;

	while (tokens && tokens->prev)
		tokens = tokens->prev;
	temp = tokens;
	i = 0;
	while (temp && ++i)
		temp = temp->next;
	cmd = ft_calloc(i + 1, sizeof(char *));
	temp = tokens;
	i = 0;
	while (temp)
	{
		cmd[i] = ft_strdup(temp->data);
		temp = temp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	try_split_else_exec(t_ast *ast_node, t_token *tokens)
{
	char	**cmd;
	if (ast_split_node(ast_node, tokens, search_type_to_split(tokens)))
		return ;
	else
	 	cmd = command_constructor(tokens);
	ast_node->type = EXEC;
	ast_node->command_list = cmd;
}

t_ast	*ast_constructor(t_token *tokens)
{
	t_ast	*root;

	root = ft_calloc(1, sizeof(t_ast));
	handle_redirect(&tokens);
	try_split_else_exec(root, tokens);
	return (root);
}
