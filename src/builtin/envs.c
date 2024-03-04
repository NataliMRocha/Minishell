/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:39:09 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/04 13:15:19 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envs	*new_envs_node(char *key, char *value)
{
	t_envs	*new_node;

	new_node = malloc(sizeof(t_envs));
	if (new_node == NULL)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

t_envs	**create_envs_table(int is_created)
{
	static t_envs	*envs;
	t_envs			*head;
	char			*tmp[2];
	int				i;

	i = -1;
	if (is_created)
		return (&envs);
	while (__environ[++i])
	{
		head = envs;
		tmp[0] = ft_strcpy_delim(__environ[i], '=');
		tmp[1] = ft_strchr(__environ[i], '=') + 1;
		while (envs && envs->next)
			envs = envs->next;
		if (!head)
			head = new_envs_node(tmp[0], tmp[1]);
		else
			envs->next = new_envs_node(tmp[0], tmp[1]);
		envs = head;
		free(tmp[0]);
	}
	return (&envs);
}

t_envs	*ft_getenv(char *key)
{
	t_envs	*envs;

	envs = *create_envs_table(1);
	while (envs)
	{
		if (ft_strncmp(envs->key, key, 125) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

int	count_envs(t_envs *envs)
{
	int	i;

	i = 0;
	while (envs)
	{
		i++;
		envs = envs->next;
	}
	return (i);
}

char	**envs_to_array(void)
{
	t_envs *envs;
	int i;
	char **environ;

	envs = *create_envs_table(1);
	i = count_envs(envs);
	environ = ft_calloc(i, sizeof(char *));
	i = 0;
	while (envs)
	{
		environ[i] = ft_strjoin(ft_strjoin(envs->key, "=", 0), envs->value, 0);
		envs = envs->next;
		i++;
	}
	environ[i] = NULL;
	return (environ);
}
