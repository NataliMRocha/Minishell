/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/16 14:19:06 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	access_path(char *path)
{
	if (ft_strchr(path, '/') && access(path, F_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (update_status_error(127));
	}
	else if (ft_strchr(path, '/') && access(path, F_OK | X_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (update_status_error(126));
	}
	return (0);
}

int	confirm_path(t_ast *root, char **path)
{
	if (!execute_builtin(root) || root->type != EXEC)
		return (1);
	*path = verify_path(root);
	if (access_path(root->cmd_list[0]) || (root->cmd_list && !*root->cmd_list))
	{
		free(*path);
		return (1);
	}
	return (0);
}

char **handle_expand(t_ast *root)
{
	char	**tmp;
	char	**split;
	int		i;
	int		j;

	tmp = ft_split(root->cmd_list[0], ' ');
	i = ft_splitlen(tmp) + ft_splitlen(root->cmd_list);
	split = ft_calloc(i, sizeof(char *));
	i = -1;
	while (tmp && tmp[++i])
		split[i] = ft_strdup(tmp[i]);
	j = 0;
	while (root && root->cmd_list && root->cmd_list[++j])
		split[i++] = ft_strdup(root->cmd_list[j]);
	split[i] = NULL;
	free_split(root->cmd_list);
	free_split(tmp);
	root->cmd_list = NULL;
	return (split);
}

void	exec(t_ast *root)
{
	char	*path;
	pid_t	pid;
	int		has_quote;

	g_last_signal = 0;
	has_quote = ft_strchr(root->cmd_list[0], '\'') || ft_strchr(root->cmd_list[0], '"');
	root->cmd_list = expanded_variable(root->cmd_list);
	if (!has_quote)
		root->cmd_list = handle_expand(root);
	if (confirm_path(root, &path))
		return ;
	pid = fork();
	if (pid == 0 && root->type == EXEC)
		handle_fork(pid, root, path);
	pid_last_exit_status(pid);
	free(path);
	if (g_last_signal == SIGINT)
		update_status_error(130);
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
	else if (root->type == BLOCK)
		handle_block(root);
	else if (root->left)
		starting_exec(root->left);
	else if (root->right)
		starting_exec(root->right);
	else if (root)
		exec(root);
}
