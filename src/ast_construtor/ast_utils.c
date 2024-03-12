/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/12 15:07:46 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*ast_holder(t_ast *root, int its_created, int is_free)
{
	static t_ast	*ast_address;

	if (root && !its_created)
		ast_address = root;
	if (root && is_free)
	{
		free_ast(ast_address);
		ast_address = NULL;
	}
	return (ast_address);
}

void	free_ast(t_ast *root)
{
	if (!root)
		return ;
	if (root && root->left)
	{
		free_ast(root->left);
		root->left = NULL;
	}
	if (root && root->right)
	{
		free_ast(root->right);
		root->right = NULL;
	}
	if (root->cmd_list)
		free_split(root->cmd_list);
	free(root);
	root = NULL;
}
