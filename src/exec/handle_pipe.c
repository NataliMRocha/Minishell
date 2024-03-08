/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:23:18 by natali            #+#    #+#             */
/*   Updated: 2024/03/08 18:13:49 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(int *fd, int std_fds)
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (std_fds)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

void	pipe_fork(int *fd, t_ast *root, int in_out)
{
	if (root && in_out == 0 && root->left->type != REDIR_OUT)
		dup2(fd[1], STDOUT_FILENO);
	else if (root && in_out == 1)
		dup2(fd[0], STDIN_FILENO);
	close_fds(fd, 0);
	if (root && in_out == 0 && root->left->type != REDIR_OUT)
	{
		starting_exec(root->left);
		save_fds(NULL, 1);
		close_fds(NULL, 1);
	}
	else if (root && in_out == 1)
	{
		starting_exec(root->right);
		save_fds(NULL, 1);
		close_fds(NULL, 1);
	}
	root = ast_holder(NULL, 1, 0);
	free_program(&root, NULL, create_envs_table(1));
	close_fds(NULL, 1);
	exit(update_status_error(-1));
}

void	exec_pipe(pid_t *intpid, int *fd, t_ast *root)
{
	intpid[0] = fork();
	if (intpid[0] < 0)
		ft_putstr_fd("fork error\n", STDERR_FILENO);
	if (intpid[0] == 0)
		pipe_fork(fd, root, 0);
	intpid[1] = fork();
	if (intpid[1] < 0)
		ft_putstr_fd("fork error\n", STDERR_FILENO);
	if (intpid[1] == 0)
		pipe_fork(fd, root, 1);
}

void	handle_pipe(t_ast *root)
{
	int		fd[2];
	pid_t	intpid[2];

	if (root->left->type == REDIR_OUT)
		starting_exec(root->left);
	if (!pipe(fd))
	{
		if (!ast_holder(NULL, 1, 0))
			root = ast_holder(NULL, 1, 0);
		exec_pipe(intpid, fd, root);
		close_fds(fd, 0);
		pid_last_exit_status(intpid[0]);
		pid_last_exit_status(intpid[1]);
	}
	else
		update_status_error(EXIT_FAILURE);
	close_fds(fd, 0);
}
