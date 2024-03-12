/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:15:02 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/12 16:39:01 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_ast *root)
{
	char *cmd;

	cmd = root->cmd_list[0];
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(root->cmd_list));
	if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(root->cmd_list));
	if (!ft_strncmp(cmd, "env", 3))
		return (print_env_list(*create_envs_table(1, 0)));
	if (!ft_strncmp(cmd, "pwd", 2))
		return (ft_pwd());
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(root->cmd_list[1]));
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (ft_echo(root->cmd_list));
	if (!ft_strncmp(cmd, "exit", 4))
	{
		ft_exit(root->cmd_list, root);
		return(0);
	}
	return (1);
}
