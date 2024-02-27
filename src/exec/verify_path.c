/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:22:38 by codespace         #+#    #+#             */
/*   Updated: 2024/02/27 16:06:43 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

char	*verify_path(t_ast *root)
{
	t_envs	*paths;
	char	**path;
	int		i;
	char	*result;

	paths = ft_getenv("PATH");
	path = ft_split(paths->value, ':');
	i = -1;
	result = NULL;
	if (access(root->command_list[0], F_OK) == 0)
		return (ft_strdup(root->command_list[0]));
	while (path && path[++i] && root->type == EXEC)
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/", 0), root->command_list[0], 0);
		if (access(path[i], F_OK) == 0)
			break;
	}
	result = ft_strdup(path[i]);
	free_split(path);
	return (result);
}
