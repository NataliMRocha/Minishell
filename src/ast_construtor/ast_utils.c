/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:54 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/23 11:11:47 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ast(t_ast *root)
{
	int	i;

	if (root)
	{
		free_ast(root->left);
		free_ast(root->right);
		if (root->command_list)
		{
			i = 0;
			while(root->command_list[i])
				free(root->command_list[i++]);
		}
		free(root->command_list);
		free(root);
	}
}
