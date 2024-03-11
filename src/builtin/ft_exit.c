/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:31 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/11 15:45:47 by egeraldo         ###   ########.fr       */
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
	while (arr[i])
		i++;
	return (i);
}

int	handle_exit_error(char **prompt)
{
	int	nb;
	
	nb = ft_atol(prompt[1]);
	if (ft_splitlen(prompt) > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if ((prompt && prompt[1]) && (!ft_isnum(prompt[1])
		|| ft_strlen(prompt[1]) != ft_intlen(nb)))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(prompt[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	return (nb);
}

void	ft_exit(char **prompt)
{
	int		i;
	char	**args;
	int		exit_status;

	args = ft_split(*prompt, ' ');
	ast_holder(NULL, 1, 1);
	free_env_list(*create_envs_table(1, 1));
	exit_status = handle_exit_error(args);
	save_fds(NULL, 1);
	i = 0;
	while (i < 3)
		close(i++);
	free_split(args);
	free(*prompt);
	rl_clear_history();
	exit(update_status_error(exit_status));
}
