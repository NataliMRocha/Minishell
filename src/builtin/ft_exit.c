/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:31 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/17 13:25:30 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_intlen(int n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
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
	if (ft_splitlen(prompt) > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	if ((prompt && tmp) && ft_strlen(tmp) != ft_intlen(nb))
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(tmp, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	return (nb);
}

void	ft_exit(char **prompt, t_ast *root)
{
	int	i;
	int	exit_status;

	free_env_list(*create_envs_table(1, 1));
	exit_status = handle_exit_error(prompt);
	save_fds(NULL, 1);
	ast_holder(root, 1, 1);
	if (!exit_status && !on_heredoc(-1))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	i = 0;
	while (i < 3)
		close(i++);
	rl_clear_history();
	exit(update_status_error(exit_status));
}
