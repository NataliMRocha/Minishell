/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:17:03 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 17:25:50 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envs	*sorted(t_envs *envs)
{
	t_envs	*tmp;
	t_envs	*tmp2;
	char	*key;
	char	*value;

	tmp = envs;
	while (tmp->next)
	{
		tmp2 = envs;
		while (tmp2->next)
		{
			if (ft_strcmp(tmp2->key, tmp2->next->key) > 0)
			{
				key = tmp2->key;
				value = tmp2->value;
				tmp2->key = tmp2->next->key;
				tmp2->value = tmp2->next->value;
				tmp2->next->key = key;
				tmp2->next->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (envs);
}

void	print_export(t_envs *envs)
{
	t_envs	*tmp;

	tmp = sorted(envs);
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	verify_key(char **key, char *var)
{
	*key = ft_strcpy_delim(var, '=');
	if ((key && *key && (*key[0] != '_' && !ft_isalpha(*key[0]))) || !*key[0])
	{
		printf("minishell: export: `%s': not a valid identifier\n", var);
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
	int		i;

	temp = *create_envs_table(1);
	if (var[0] && !var[1])
	{
		print_export(temp);
		return (update_status_error(0));
	}
	i = 0;
	while (var[++i])
	{
		while (temp->next->next)
			temp = temp->next;
		if (strchr(var[i], '=') && ft_put_new_env(&key, var[i], temp))
		{
			update_status_error(1);
			return (0);
		}
	}
	return (update_status_error(0));
}
