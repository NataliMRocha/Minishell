/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:17:03 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/11 22:28:32 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**sorted(void)
{
	char	**vars;
	char 	*tmp;
	int		i;
	int		j;

	vars = envs_to_array(0);
	i = 0;
	while (vars[i])
	{
		j = i + 1;
		while (vars[j])
		{
			if (ft_strcmp(vars[i], vars[j]) > 0)
			{
				tmp = vars[i];
				vars[i] = vars[j];
				vars[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (vars);
}

void	print_export()
{
	char	**arr;
	int		i;
	char	*key;
	char	*value;

	arr = sorted();
	i = -1;
	while (arr && arr[++i])
	{
		key = ft_strcpy_delim(arr[i], '=');
		value = ft_strchr(arr[i], '=');
		printf("declare -x %s=\"%s\"\n", key, &value[1]);
		free(key);
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

int	ft_put_new_env(char **key, char *var)
{
	char	*value;
	t_envs	*envs;
	t_envs	*new_node;

	envs = *create_envs_table(1, 0);
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

	temp = *create_envs_table(1, 0);
	if (var[0] && !var[1])
	{
		print_export();
		return (update_status_error(0));
	}
	i = 0;
	while (var[++i])
	{
		while (temp->next->next)
			temp = temp->next;
		if (strchr(var[i], '=') && ft_put_new_env(&key, var[i]))
		{
			update_status_error(1);
			return (0);
		}
	}
	return (update_status_error(0));
}
