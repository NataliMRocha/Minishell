/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:17:32 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/18 16:42:21 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_fork(int status)
{
	static int	on_fork;

	if (status == 1)
		on_fork = status;
	return (on_fork);
}

int	is_after_prompt(int is_after)
{
	static int	after;

	if (is_after != -1)
		after = is_after;
	return (after);
}

int	on_heredoc(int on_heredoc)
{
	static int	heredoc;

	if (on_heredoc != -1)
		heredoc = on_heredoc;
	return (heredoc);
}

void	sigquit_case(void)
{
	if (update_status_error(-1) == 131)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		term_properties(1);
	}
	else
		term_properties(0);
}
