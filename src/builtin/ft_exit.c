/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:27:31 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/11 14:59:25 by egeraldo         ###   ########.fr       */
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

int	non_numeric(char *prompt)
{
	int	nb;

	prompt = ft_strchr(prompt, ' ');
	nb = ft_atol(prompt);
	if (prompt && ft_strlen(prompt + 1) != ft_intlen(nb))
	{
		printf("\n\nTESTES\n\n");
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(prompt, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	return (nb);
}

void	ft_exit(char **prompt)
{
	int	i;

	ast_holder(NULL, 1, 1);
	free_env_list(*create_envs_table(1, 1));
	save_fds(NULL, 1);
	i = 0;
	while (i < 3)
		close(i++);
	i = non_numeric(*prompt);
	free(*prompt);
	rl_clear_history();
	exit(update_status_error(i));
}
