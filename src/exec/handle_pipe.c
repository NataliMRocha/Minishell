/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:23:18 by natali            #+#    #+#             */
/*   Updated: 2024/02/27 17:16:50 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void	pipe_fork(int *fd, t_ast *root, int in_out)
{
	if (in_out == 0 && root->left->type != REDIR_OUT)
		dup2(fd[1], STDOUT_FILENO);
	else if (in_out == 1)
		dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
	if (in_out == 0 && root->left->type != REDIR_OUT)
	{
		starting_exec(root->left);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	else if (in_out == 1)
	{
		starting_exec(root->right);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	free_program(&root, NULL, NULL, create_envs_table(1));
	exit(update_status_error(0));
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

void handle_pipe(t_ast *root)
{
	int		fd[2];
	int		status_code;
	pid_t	intpid[2];

	if (root->left->type == REDIR_OUT)
		starting_exec(root->left);
	if (!pipe(fd))
	{
		exec_pipe(intpid, fd, root);
		close(fd[0]);
		close(fd[1]);
		waitpid(intpid[1], &status_code, 0);
		waitpid(intpid[0], &status_code, 0);
		update_status_error(status_code);
	}
	else
		update_status_error(EXIT_FAILURE);
	close(fd[0]);
	close(fd[1]);
}
