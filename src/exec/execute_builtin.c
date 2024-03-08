/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:15:02 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/08 18:12:17 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_ast *root)
{
	if (!ft_strncmp(root->cmd_list[0], "export", 6))
		return (ft_export(root->cmd_list));
	return (1);
}
