/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:32:50 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/13 17:55:34 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_envs(char *pwd_name, char *path)
{
	char	**env;

	env = ft_calloc(3, sizeof(char *));
	env[0] = ft_strdup("export");
	env[1] = ft_strjoin(ft_strjoin(pwd_name, "=", 0), path, 1);
	env[2] = NULL;
	free(path);
	ft_export(env);
	free_split(env);
}

int	ft_cd(char *path)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_calloc(1024, sizeof(char));
	pwd = ft_calloc(1024, sizeof(char));
	getcwd(oldpwd, 1024);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		free(oldpwd);
		free(pwd);
		update_status_error(1);
		return (0);
	}
	getcwd(pwd, 1024);
	update_envs("OLDPWD", oldpwd);
	update_envs("PWD", pwd);
	return (update_status_error(0));
}
