/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/29 18:31:10 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_ast *root)
{
	char	*path;
	int		status;
	pid_t	i;

	path = verify_path(root);
	status = update_status_error(-1);
	i = fork();
	if (i == 0 && root->type == EXEC)
	{
		if (execve(path, root->command_list, NULL) < 0)
		{
			ft_putstr_fd("command not found: ", STDERR_FILENO);
			ft_putstr_fd(root->command_list[0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			root = ast_holder(NULL, 1);
			free_program(&root, &path, create_envs_table(1));
			close_fds(NULL, 1);
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

	starting_exec(root->left);
	status_code = update_status_error(-1);
	if((!status_code) && root->type == AND)
		starting_exec(root->right);
	else if (status_code && root->type == OR)
		starting_exec(root->right);
}

void starting_exec(t_ast *root)
{
	if(root->type == AND || root->type == OR)
		handle_and_or(root);
	else if (root->type == PIPE)
		handle_pipe(root);
	else if (check_redirect(root))
		handle_redir(root);
	else if(root->left)
		starting_exec(root->left);
	else if(root->right)
		starting_exec(root->right);
	else if(root)
		exec(root);
}