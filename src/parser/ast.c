#include <stdlib.h>
#include <stdio.h>
#include "../../includes/minishell.h"

typedef struct s_ast
{
	char *content;
	struct s_ast *right;
	struct s_ast *left;
} t_ast;

t_ast	*new_node(char *content)
{
	t_ast *node = (t_ast *)calloc(sizeof(t_ast), 1);
	node->content = content;
	return (node);
}

t_ast	*insert_node(t_ast *root, char *content)
{
	t_ast	*node;

	if  (root == NULL)
		root = new_node(content);
	else if (ft_strchr("|&><", *content))
	{
		node = new_node(content);
		node->left = root;
		root = node;
	}
	else
		root->right = new_node(content);
	return (root);
}



// TODO: apagar essas funções
/*
void	print_ast(t_ast *root)
{
	if (root)
	{
		print_ast(root->left);
		printf("%s ", root->content);
		print_ast(root->right);
	}
}

int main()
{
	t_ast *root = NULL;
	char *comandos[] = {"cmd1", "|", "cmd2", "|", "cmd3", "|", "cmd4", NULL};
	int i = 0;

	while (comandos[i])
		root = insert_node(root, comandos[i++]);

	print_ast(root);
	printf("\n\n");
	return 0;
}
*/