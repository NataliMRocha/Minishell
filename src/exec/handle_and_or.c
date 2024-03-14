/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:30:08 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/14 16:30:36 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_and_or(t_ast *root)
{
	int	status_code;

	starting_exec(root->left);
	status_code = update_status_error(-1);
	if ((!status_code) && ast_holder(NULL, 1, 0) && root->type == AND)
		starting_exec(root->right);
	else if (status_code && ast_holder(NULL, 1, 0) && root->type == OR)
		starting_exec(root->right);
}
