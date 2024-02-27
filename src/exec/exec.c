/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/27 17:08:30 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_ast *root)
{
	char	*path;
	int		status;
	pid_t	i;

	if (root->left || root->right)
		starting_exec(root);
	path = verify_path(root);
	status = ft_atoi(ft_getenv("?")->value);
	i = fork();
	if (i == 0 && root->type == EXEC)
	{
		if (path && execve(path, root->command_list, NULL) < 0)
			printf("deu ruim\n");
		else
		{
			printf("comando não encontrado\n");
			free_program(&root, NULL, NULL, create_envs_table(1));
			exit(update_status_error(127));
		}
	}
	wait(&status);
	free(path);
	update_status_error(status);
}

void handle_and_or(t_ast *root)
{
	int status_code;

	exec(root->left);
	status_code = ft_atoi(ft_getenv("?")->value);
	if((!status_code) && root->type == AND)
		exec(root->right);
	else if (status_code && root->type == OR)
		exec(root->right);
}

void starting_exec(t_ast *root)
{
	if(root->type == AND || root->type == OR)
		handle_and_or(root);
	else if (root->type == PIPE)
		handle_pipe(root);
	else if(root->left)
		starting_exec(root->left);
	else if(root->right)
		starting_exec(root->right);
	else if(root)
		exec(root);
}