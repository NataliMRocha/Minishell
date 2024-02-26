/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/26 20:39:25 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec(t_ast *root)
{
	char	*path;
	int		status;
	pid_t	i;

	starting_exec(root);
	path = verify_path(root);
	status = ft_atoi(ft_getenv("?")->value);
	i = fork();
	if (i == 0 && root->type == EXEC)
	{
		if (execve(path, root->command_list, NULL) < 0)
			printf("deu ruim\n");
	}
	wait(&status);
	update_status_error(ft_itoa(status));
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
/* 	else if(root->left)
		starting_exec(root->left);
	else if(root->right)
		starting_exec(root->right);
	//aqui ele estaria no começo da linha de comando?
	else if(!root->left)
		exec(root); */
}