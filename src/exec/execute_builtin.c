/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:15:02 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/13 17:12:11 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_ast *root)
{
	char *cmd;

	cmd = root->cmd_list[0];
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (ft_export(root->cmd_list));
	if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(root->cmd_list));
	if (!ft_strcmp(cmd, "env"))
		return (print_env_list(*create_envs_table(1, 0)));
	if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(root->cmd_list[1]));
	if (!ft_strcmp("echo", cmd))
		return (ft_echo(root->cmd_list));
	if (!ft_strcmp(cmd, "exit"))
	{
		ft_exit(root->cmd_list, root);
		return(0);
	}
	return (1);
}
