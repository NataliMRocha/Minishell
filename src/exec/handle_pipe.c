/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:23:18 by natali            #+#    #+#             */
/*   Updated: 2024/02/26 20:55:36 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_fork(int *fd, t_ast *root, int in_out)
{
	//SE ESTOU NO FD[0] E NÃO TEM UM REDIRECT OUT ANTES, TROCA O OUTPUT
	//ESCREVE NO PIPE
	if (in_out == 0 && root->left->type != REDIR_OUT)
		dup2(fd[1], STDOUT_FILENO);
	//FD[1] TROCO O FD DE INPUT PARA LER DO PIPE
	else if (in_out == 1)
		dup2(fd[0], STDIN_FILENO);
	//EXECUTO O NÓ DA ESQUERDA ESCREVENDO NO PIPE
	if (in_out == 0 && root->left->type != REDIR_OUT)
		exec(root->left);
	else if (in_out == 1)
		exec(root->right);
    close(fd[0]);
    close(fd[1]);
    exit(0);
}

void handle_pipe(t_ast *root)
{
	int	fd[2];
	int	status_code;
	pid_t	intpid[2];

	if (root->left->type == REDIR_OUT)
		starting_exec(root->left);
	if (pipe(fd) == 0)
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
			pipe_fork(fd, root, 0);
		close(fd[0]);
		close(fd[1]);
		waitpid(intpid[0], &status_code, 0);
		waitpid(intpid[1], &status_code, 0);
		update_status_error(ft_itoa(status_code));
	}
	else
		update_status_error(ft_itoa(EXIT_FAILURE));
}