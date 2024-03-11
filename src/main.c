/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/11 17:42:15 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pid_last_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 139)
		status = 1;
	update_status_error(status);
}

int	update_status_error(int exit_status)
{
	static int	status;

	if (exit_status != -1)
		status = exit_status;
	return (status);
}

void	free_program(t_ast **root, char **get_cmd, t_envs **var_envs)
{
	if (get_cmd && *get_cmd)
		free(*get_cmd);
	if (root && *root)
	{
		free_ast(*root, 0);
		*root = NULL;
	}
	if (var_envs && *var_envs)
		free_env_list(*var_envs);
}

int	main(void)
{
	t_ast	*root;
	char	*get_cmd;

	// setup_signals();
	create_envs_table(0, 0);
	root = NULL;
	while (1)
	{
		get_cmd = ft_readline();
		root = parser(get_cmd);
		if (!root)
			continue ;
		starting_exec(root);
		root = ast_holder(NULL, 1, 0);
		free_program(&root, &get_cmd, NULL);
	}
	free_program(&root, &get_cmd, create_envs_table(1, 1));
	close_fds(NULL, 1);
	return (0);
}
