/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/29 10:38:11 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ast(t_ast *root)
{
	int	i;

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
	if (root->command_list)
	{
		i = 0;
		while(root->command_list[i] && *root->command_list[i])
			free(root->command_list[i++]);
		free(root->command_list);
		root->command_list = NULL;
	}
	free(root);
	root = NULL;
}
