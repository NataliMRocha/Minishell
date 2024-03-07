/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:46:31 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 12:31:00 by egeraldo         ###   ########.fr       */
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

int	ft_puterror(char *cmd, char *str, t_ast *root)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	update_status_error(1);
	free_ast(root, 1);
	root = NULL;
	return (0);
}