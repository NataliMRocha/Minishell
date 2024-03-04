/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/04 16:56:32 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expanded_variable(char **cmd_list)
{
	char	**expanded;
	int		i;
	int		j;

	i = -1;
	expanded = NULL;
	while (cmd_list && cmd_list[++i])
		cmd_list[i] = expand_var(cmd_list[i]);
	expanded = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (cmd_list[++i])
		if (*cmd_list[i])
			expanded[j++] = ft_strdup(cmd_list[i]);
	free_split(cmd_list);
	cmd_list = NULL;
	return (expanded);
}

void	exec_error(char *cmd)
{
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	exec(t_ast *root)
{
	char	*path;
	int		status;
	pid_t	i;
	char	**envs;

	status = update_status_error(-1);
	i = -1;
	root->cmd_list = expanded_variable(root->cmd_list);
	path = verify_path(root);
	i = fork();
	if (i == 0 && root->type == EXEC)
	{
		i = -1;
		envs = envs_to_array();
		if (execve(path, root->cmd_list, envs) == 0)
			;
		else if (path && *path == '0')
			exec_error(root->cmd_list[0]);
		root = ast_holder(NULL, 1);
		free_split(envs);
		free_program(&root, &path, create_envs_table(1));
		close_fds(NULL, 1);
		exit(update_status_error(127));
	}
	wait(&status);
	free(path);
	update_status_error(status);
}

void	handle_and_or(t_ast *root)
{
	int	status_code;

	starting_exec(root->left);
	status_code = update_status_error(-1);
	if ((!status_code) && root->type == AND)
		starting_exec(root->right);
	else if (status_code && root->type == OR)
		starting_exec(root->right);
}

void	starting_exec(t_ast *root)
{
	if (root->type == AND || root->type == OR)
		handle_and_or(root);
	else if (root->type == PIPE)
		handle_pipe(root);
	else if (check_redirect(root))
		handle_redir(root);
	else if(root->left)
		starting_exec(root->left);
	else if (root->right)
		starting_exec(root->right);
	else if (root)
		exec(root);
}
