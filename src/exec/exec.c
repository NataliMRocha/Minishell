/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/26 12:10:45 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec(t_ast *root)
{
	t_envs *paths;
	char **path;
	int i;
	int j;

	starting_exec(root);
	paths = ft_getenv("PATH");
	path = ft_split(paths->value, ':');
	i = -1;
	while (path && path[++i] && root->type == EXEC)
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/", 0), root->command_list[0], 0);
		if (access(path[i], F_OK) == 0)
			break;
	}
	j = fork();
	if (j == 0)
		if (execve(path[i], root->command_list, NULL) < 0)
			printf("deu ruim\n");
	waitpid(i, NULL, 0);
}

void handle_and_or(t_ast *root)
{
	t_envs *status_code;

	status_code = ft_getenv("?");
	exec(root->left);
	if((!status_code->value && root->type == AND))
		exec(root->right);
	else if (status_code->value && root->type == OR)
		exec(root->right);
}

void starting_exec(t_ast *root)
{
	if(root->type == AND || root->type == OR)
		handle_and_or(root);
}
