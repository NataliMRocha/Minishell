/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:01:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/06 11:40:39 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_and_close(int *std_fd)
{
	if (!std_fd && !*std_fd)
		return ;
	dup2(std_fd[1], STDOUT_FILENO);
	dup2(std_fd[0], STDIN_FILENO);
	close_fds(std_fd, 0);
}

void	free_list(t_fds **fds)
{
	t_fds	*tmp;

	if (!fds || !*fds)
		return ;
	while (*fds)
	{
		tmp = (*fds)->next;
		free(*fds);
		*fds = tmp;
	}
}

int	check_redirect(t_ast *root)
{
	if (root->type == REDIR_IN || root->type == REDIR_OUT
		|| root->type == REDIR_APPEND)
		return (1);
	return (0);
}

int	ft_puterror(char *cmd, char *str, t_ast *root)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	update_status_error(1);
	free_ast(root, 1);
	root = NULL;
	return (0);
}

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

int	is_redir_in(char *name, t_ast *root)
{
	int	fd;

	if (!access(name, F_OK))
	{
		fd = open(name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (access(name, W_OK | R_OK))
		return (ft_puterror(name, ": Permission denied\n", root));
	else
		return (ft_puterror(name, ": No such file or directory\n", root));
	return (1);
}

int	is_redir_out(char *name, int type, t_ast *root)
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
		return (ft_puterror(name, ": Permission denied\n", root));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

void	get_fds(t_ast *root)
{
	if (root->left && check_redirect(root->left))
	{
		fds_list(root->right->cmd_list, root->type);
		get_fds(root->left);
	}
	if (root->left->type == EXEC && check_redirect(root) && root->right)
		fds_list(root->right->cmd_list, root->type);
}
void	handle_fds(t_ast *root)
{
	t_fds	**fds;
	t_fds	*tmp;
	fds = fds_list(NULL, 0);
	tmp = *fds;
	while (tmp)
	{
		if (tmp->type == REDIR_IN && !is_redir_in(tmp->name[0], root->left))
			root = NULL;
		else if ((tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
			&& !is_redir_out(tmp->name[0], tmp->type, root->left))
			root = NULL;
		if (!root)
			break;
		tmp = tmp->next;
	}
	free_list(fds);
}
void	handle_redir(t_ast *root)
{
	int		std_fd[2];


	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (fds_list(NULL, 0) && !*fds_list(NULL, 0))
		get_fds(root);
	if (root->left->type == EXEC)
		handle_fds(root->left);
	starting_exec(root->left);
	dup_and_close(std_fd);
}
