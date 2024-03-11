/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/11 17:16:55 by natali           ###   ########.fr       */
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

void	exec_error(char *cmd, char **path)
{
	if (path && *path && *path[0] == '0')
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	update_status_error(127);
	save_fds(NULL, 1);
	ast_holder(NULL, 1, 1);
	create_envs_table(1, 1);
	free(*path);
	close_fds(NULL, 1);
}

void	exec(t_ast *root)
{
	char	*path;
	pid_t	i;
	char	**envs;

	i = -1;
	root->cmd_list = expanded_variable(root->cmd_list);
	if (!execute_builtin(root))
		return ;
	path = verify_path(root);
	if (root->cmd_list && !*root->cmd_list)
		return (free(path));
	i = fork();
	if (i == 0 && root->type == EXEC)
	{
		envs = envs_to_array();
		if (execve(path, root->cmd_list, envs) == 0)
			;
		else
			exec_error(root->cmd_list[0], &path);
		free_split(envs);
		free_program(&root, NULL, create_envs_table(1, 1));
		exit(update_status_error(127));
	}
	pid_last_exit_status(i);
	free(path);
}

void	handle_and_or(t_ast *root)
{
	int	status_code;

	starting_exec(root->left);
	status_code = update_status_error(-1);
	if ((!status_code) && ast_holder(NULL, 1, 0) && root->type == AND)
		starting_exec(root->right);
	else if (status_code && ast_holder(NULL, 1, 0) && root->type == OR)
		starting_exec(root->right);
}

void	starting_exec(t_ast *root)
{
	if (!root)
		return ;
	if (root->type == AND || root->type == OR)
		handle_and_or(root);
	else if (root->type == PIPE)
		handle_pipe(root);
	else if (is_redirect(root->type))
		handle_redir(root);
	else if (root->left)
		starting_exec(root->left);
	else if (root->right)
		starting_exec(root->right);
	else if (root)
		exec(root);
}
