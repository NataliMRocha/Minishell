/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:01:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/04 12:55:09 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    check_redirect(t_ast *root)
{
    if(root->type == REDIR_IN || root->type == REDIR_OUT
        || root->type == REDIR_APPEND)
        return (1);
    return (0);
}

int    is_redir_in(t_ast *root)
{
    if (!root->fd)
        root->fd = open(root->command_list[0], O_RDONLY);
    if (root->fd < 0)
    {
        update_status_error(1);
        if (access(root->command_list[0], F_OK))
        {
            ft_putstr_fd(root->command_list[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            return (0);
        }
        if (access(root->command_list[0], W_OK | R_OK))
        {
            ft_putstr_fd(root->command_list[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
        }
        return (0);
    }
    dup2(root->fd, STDIN_FILENO);
    close(root->fd);
    return (1);
}

int    is_redir_out(t_ast *root)
{
    if (!root->fd)
    {
        root = root->right;
        root->fd = open(root->command_list[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
    }
    else if (!root->right->fd && root->type == REDIR_APPEND)
    {
        root = root->right;
        root->fd = open(root->command_list[0], O_RDWR | O_CREAT | O_APPEND, 0666);
    }
    if (root->fd < 0)
    {
        if (access(root->command_list[0], W_OK | R_OK))
        {
            ft_putstr_fd(root->command_list[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
            update_status_error(1);
        }
        return (0);
    }
    dup2(root->fd, STDOUT_FILENO);
    close(root->fd);
    return (1);
}

void    handle_redir(t_ast *root)
{
    static int std_fd[2];

    std_fd[0] = dup(STDIN_FILENO);
    std_fd[1] = dup(STDOUT_FILENO);
    if (root->left && check_redirect(root->left))
        handle_redir(root->left);
    if (root->type == REDIR_OUT || root->type == REDIR_APPEND)
    {
        if (!is_redir_out(root))
        {
		    close_fds(std_fd, 0);
            return ;
        }
    }
    else if(root->type == REDIR_IN)
    {
        if (!is_redir_in(root->right))
        {
		    close_fds(std_fd, 0);
            return ;
        }
    }
    starting_exec(root->left);
    dup2(std_fd[1], STDOUT_FILENO);
    dup2(std_fd[0], STDIN_FILENO);
    close_fds(std_fd, 0);
}
