/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:15:06 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/14 18:18:29 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_fork(int pid, t_ast *root, char *path)
{
	char	**envs;

	if (pid == 0 && root->type == EXEC)
	{
		is_fork(1);
		signal(SIGINT, SIG_DFL);
		envs = envs_to_array();
		if (execve(path, root->cmd_list, envs) == 0)
			;
		else
			exec_error(root->cmd_list[0], &path);
		free_split(envs);
		free_program(NULL, NULL, create_envs_table(1, 1));
		exit(update_status_error(127));
	}
}
