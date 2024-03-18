/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:32:50 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/14 14:11:13 by etovaz           ###   ########.fr       */
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

int	print_cd_error(char *path, char *oldpwd, char *pwd)
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

int	cd_error(char **path)
{
	if (path && *path && ft_splitlen(path) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (update_status_error(1));
	}
	return (0);
}

int	check_home(char *path)
{
	t_envs	*tmp;

	tmp = NULL;
	if (path == NULL || path[0] == '~')
	{
		tmp = ft_getenv("HOME");
		if (!tmp)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (update_status_error(1));
		}
		chdir(tmp->value);
		update_status_error(0);
		return (1);
	}
	return (0);
}

int	ft_cd(char **cmd)
{
	char	*oldpwd;
	char	*pwd;
	char	*path;

	path = cmd[1];
	if (check_home(path) || cd_error(cmd))
		return (0);
	oldpwd = ft_calloc(1024, sizeof(char));
	pwd = ft_calloc(1024, sizeof(char));
	getcwd(oldpwd, 1024);
	if (chdir(path) == -1)
		return (print_cd_error(path, oldpwd, pwd));
	getcwd(pwd, 1024);
	update_envs("OLDPWD", oldpwd);
	update_envs("PWD", pwd);
	return (update_status_error(0));
}
