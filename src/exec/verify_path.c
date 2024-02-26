/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:22:38 by codespace         #+#    #+#             */
/*   Updated: 2024/02/26 21:35:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*verify_path(t_ast *root)
{
	t_envs	*paths;
	char	**path;
	int		i;

	paths = ft_getenv("PATH");
	path = ft_split(paths->value, ':');
	i = -1;

	if (access(root->command_list[0], F_OK) == 0)
		return (ft_strdup(root->command_list[0]));
	while (path && path[++i] && root->type == EXEC)
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/", 0), root->command_list[0], 0);
		if (access(path[i], F_OK) == 0)
			return (path[i]);
	}
	return (NULL);
}