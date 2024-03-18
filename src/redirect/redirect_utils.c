/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:46:31 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 16:36:01 by etovaz           ###   ########.fr       */
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

int	ft_puterror(char *cmd, char *str)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	update_status_error(1);
	return (0);
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
