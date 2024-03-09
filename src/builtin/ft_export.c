/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:17:03 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 15:24:15 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_envs *envs)
{
	t_envs	*tmp;

	tmp = envs;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

int	verify_key(char **key, char *var)
{
	*key = ft_strcpy_delim(var, '=');
	if (key && *key && (*key[0] && *key[0] == '?'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", *key);
		free(*key);
		return (1);
	}
	return (0);
}

int	ft_put_new_env(char **key, char *var, t_envs *envs)
{
	char	*value;
	t_envs	*new_node;

	if (verify_key(key, var))
		return (update_status_error(1));
	value = ft_remove_quotes(ft_strchr(var, '=') + 1);
	new_node = ft_getenv(*key);
	if (new_node)
	{
		free(new_node->value);
		new_node->value = ft_strdup(value);
	}
	else
		envs->next->next = new_envs_node(*key, value);
	free(*key);
	free(value);
	return (update_status_error(0));
}

int	ft_export(char **var)
{
	t_envs	*temp;
	char	*key;

	temp = *create_envs_table(1);
	if (var[0] && !var[1])
	{
		print_export(temp);
		return (update_status_error(0));
	}
	while (temp->next->next)
		temp = temp->next;
	if (strchr(var[1], '=') && ft_put_new_env(&key, var[1], temp))
		return (update_status_error(1));
	return (update_status_error(0));
}
