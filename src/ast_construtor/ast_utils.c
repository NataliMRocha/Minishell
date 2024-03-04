/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/04 16:16:47 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*ast_holder(t_ast *root, int its_created)
{
	static t_ast	*ast_address;

	if (root && !its_created)
		ast_address = root;
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
	if(root && root->right)
	{
		free_ast(root->right);
		root->right = NULL;
	}
	if (root->cmd_list)
		free_split(root->cmd_list);
	free(root);
	root = NULL;
	root = ast_holder(root, 0);
}
