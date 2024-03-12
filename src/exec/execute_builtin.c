/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:15:02 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/11 23:04:04 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_ast *root)
{
	if (!ft_strncmp(root->cmd_list[0], "export", 6))
		return (ft_export(root->cmd_list));
	if (!ft_strncmp(root->cmd_list[0], "unset", 5))
		return (ft_unset(root->cmd_list));
	if (!ft_strncmp(root->cmd_list[0], "env", 3))
		return (print_env_list(*create_envs_table(1, 0)));
	if (!ft_strncmp(root->cmd_list[0], "pwd", 2))
		return (ft_pwd());
	if (!ft_strncmp(root->cmd_list[0], "cd", 2))
		return (ft_cd(root->cmd_list[1]));
	if (!ft_strncmp("echo", root->cmd_list[0], ft_strlen(root->cmd_list[0])))
		return (ft_echo(root->cmd_list));
	if (!ft_strncmp(root->cmd_list[0], "exit", 4))
	{
		ft_exit(root->cmd_list, root);
		return(0);
	}
	return (1);
}
