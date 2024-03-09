/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:15:02 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 19:04:59 by etovaz           ###   ########.fr       */
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
	return (1);
}
