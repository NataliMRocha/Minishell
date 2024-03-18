/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:01:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 16:34:57 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_in(char *name)
{
	int	fd;

	if (!access(name, F_OK))
	{
		fd = open(name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (!access(name, F_OK) && access(name, W_OK | R_OK))
		return (ft_puterror(name, ": Permission denied\n"));
	else if ((name[0] == '.' || name[0] == '/') && !access(name, F_OK))
		return (ft_puterror(name, ": Is a directory\n"));
	else
		return (ft_puterror(name, ": No such file or directory\n"));
	return (1);
}

int	is_redir_out(char *name, int type)
{
	int	fd;

	fd = -1;
	if (type == REDIR_OUT)
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (type == REDIR_APPEND)
	{
		if (access(name, F_OK))
			fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
		else
			fd = open(name, O_RDWR | O_APPEND, 0666);
	}
	if (fd < 0 && access(name, F_OK))
		return (ft_puterror(name, ": No such file or directory\n"));
	if (fd < 0 && access(name, W_OK | R_OK))
		return (ft_puterror(name, ": Permission denied\n"));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	get_fds(t_ast *root)
{
	char	*name;

	if (root->left)
	{
		name = ft_remove_quotes(root->right->cmd_list[0]);
		free(root->right->cmd_list[0]);
		root->right->cmd_list[0] = ft_strdup(name);
		fds_list(root->right->cmd_list, root->type);
		get_fds(root->left);
		free(name);
	}
	if (root->left && root->left->type == EXEC && is_redirect(root->type)
		&& root->right)
	{
		name = ft_remove_quotes(root->right->cmd_list[0]);
		free(root->right->cmd_list[0]);
		root->right->cmd_list[0] = ft_strdup(name);
		fds_list(root->right->cmd_list, root->type);
		free(name);
	}
}

int	handle_fds(void)
{
	t_fds	**fds;
	t_fds	*tmp;
	int		control;

	control = 1;
	fds = fds_list(NULL, 0);
	tmp = *fds;
	while (tmp)
	{
		if ((tmp->type == REDIR_IN || tmp->type == HEREDOC)
			&& !is_redir_in(tmp->name[0]))
			control = 0;
		else if ((tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			&& !is_redir_out(tmp->name[0], tmp->type))
			control = 0;
		if (!control)
			break ;
		tmp = tmp->next;
	}
	free_list(fds);
	if (!control)
		return (0);
	return (1);
}

void	handle_redir(t_ast *root)
{
	int	std_fd[2];

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (fds_list(NULL, 0) && !*fds_list(NULL, 0))
		get_fds(root);
	if ((root->left->type == EXEC || root->left->type == WORD) && !handle_fds())
	{
		dup_and_close(std_fd);
		return ;
	}
	save_fds(std_fd, 0);
	starting_exec(root->left);
	dup_and_close(std_fd);
}
