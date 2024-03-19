/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:31 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/19 10:33:11 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_intlen(int n)
{
	int	len;

	if (n < 0)
		n = -n;
	len = 1;
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_splitlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	handle_exit_error(char **prompt)
{
	int		nb;
	char	*tmp;

	if (!prompt)
		return (0);
	nb = ft_atol(prompt[1]);
	if (prompt[1] && (prompt[1][0] == '+' || prompt[1][0] == '-'))
		tmp = &prompt[1][1];
	else
		tmp = prompt[1];
	if ((prompt && tmp && ft_strlen(tmp) != ft_intlen(nb)) || (tmp && !ft_isnum(tmp)))
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(tmp, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		update_status_error(2);
		return (-2);
	}
	if (ft_splitlen(prompt) > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", STDERR_FILENO);
		update_status_error(1);
		return (-1);
	}
	return (nb);
}

void	ft_exit(char **prompt, t_ast *root)
{
	int	i;
	int	exit_status;

	exit_status = handle_exit_error(prompt);
	if (exit_status != -1)
	{
		free_env_list(*create_envs_table(1, 1));
		save_fds(NULL, 1);
		ast_holder(root, 1, 1);
		if (exit_status > 0 && !on_heredoc(-1))
			ft_putstr_fd("exit\n", STDERR_FILENO);
		i = 0;
		while (i < 3)
			close(i++);
		rl_clear_history();
		exit(update_status_error(exit_status));
	}
	return ;
}
