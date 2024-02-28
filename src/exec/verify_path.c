/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:22:38 by codespace         #+#    #+#             */
/*   Updated: 2024/02/28 12:49:10 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
}

char	*verify_path(t_ast *root)
{
	t_envs	*paths;
	char	**path;
	int		i;
	char	*result;

	if (access(root->command_list[0], F_OK) == 0)
		return (ft_strdup(root->command_list[0]));
	paths = ft_getenv("PATH");
	path = ft_split(paths->value, ':');
	i = -1;
	while (path && path[++i] && root->type == EXEC)
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/", 1), root->command_list[0], 1);
		if (access(path[i], F_OK) == 0)
			break;
	}
	result = ft_strdup(path[i]);
	free_split(path);
	if (result)
		return (result);
	return (ft_strdup("0"));
}
