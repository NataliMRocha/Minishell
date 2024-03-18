/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:26:08 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 16:26:16 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	term_properties(int restore)
{
	static struct termios	term;

	if (!restore)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sigint_handler(int signal)
{
	g_last_signal = signal;
	if (is_fork(-1))
	{
		free_split(envs_to_array());
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	ast_holder(NULL, 1, 1);
	if (on_heredoc(-1))
		close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 1);
	if (!is_after_prompt(-1))
		rl_redisplay();
	update_status_error(130);
}

void	signals_initializer(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR || signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		ft_putendl_fd("fail to set signals", 2);
		exit(EXIT_FAILURE);
	}
}
