/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:33:43 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/13 17:53:58 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[i] && !ft_strncmp(args[i], "-n", 3))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (update_status_error(0));
}