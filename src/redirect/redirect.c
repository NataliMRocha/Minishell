/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:01:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/12 21:10:14 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_fds	**fds_list(char **name, int type)
{
	static t_fds	*fds;
	t_fds			*new;

	if (!name && !type)
		return (&fds);
	new = malloc(sizeof(t_fds));
	new->name = name;
	new->type = type;
	new->next = NULL;
	new->next = fds;
	fds = new;
	return (&fds);
}

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
	if (fd < 0 && access(name, W_OK | R_OK))
		return (ft_puterror(name, ": Permission denied\n"));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	get_fds(t_ast *root)
{
	if (root->left && is_redirect(root->left->type))
	{
		fds_list(root->right->cmd_list, root->type);
		get_fds(root->left);
	}
	if (root->left->type == EXEC && is_redirect(root->type) && root->right)
		fds_list(root->right->cmd_list, root->type);
}

int	handle_fds(t_ast *root)
{
	t_fds	**fds;
	t_fds	*tmp;

	fds = fds_list(NULL, 0);
	tmp = *fds;
	while (tmp)
	{
		if ((tmp->type == REDIR_IN || tmp->type == HEREDOC)
			&& !is_redir_in(tmp->name[0]))
			root = NULL;
		else if ((tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			&& !is_redir_out(tmp->name[0], tmp->type))
			root = NULL;
		if (!root)
			break ;
		tmp = tmp->next;
	}
	free_list(fds);
	if (!root)
		return (0);
	return (1);
}

void	save_fds(int *fds, int close_fds)
{
	static int	save[2];

	if (!close_fds)
	{
		save[0] = fds[0];
		save[1] = fds[1];
	}
	if (*save && close_fds)
	{
		close(save[0]);
		close(save[1]);
	}
}

void	handle_redir(t_ast *root)
{
	int	std_fd[2];

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (fds_list(NULL, 0) && !*fds_list(NULL, 0))
		get_fds(root);
	if (root->left->type == EXEC && !handle_fds(root->left))
		root->left->type = ARCHIVE;
	save_fds(std_fd, 0);
	if (root)
		starting_exec(root->left);
	dup_and_close(std_fd);
}
