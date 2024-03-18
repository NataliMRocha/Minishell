/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:15:02 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 16:13:14 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_ast *root)
{
	char	*cmd;

	cmd = root->cmd_list[0];
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (ft_export(root->cmd_list));
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (ft_unset(root->cmd_list));
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (print_env_list(*create_envs_table(1, 0)));
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (ft_pwd());
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (ft_cd(root->cmd_list));
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (ft_echo(root->cmd_list));
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
	{
		ft_exit(root->cmd_list, root);
		return (0);
	}
	return (1);
}
