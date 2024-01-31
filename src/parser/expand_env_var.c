/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/31 17:46:12 by egeraldo         ###   ########.fr       */
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

t_envs **create_envs_table(void)
{
	static t_envs	*envs;
	t_envs			*head;
	char			**tmp;
	int				i;

	i = -1;
	while (__environ[++i])
	{
		tmp = ft_split(__environ[i], '=');
		if (envs == NULL)
			envs = new_envs_node(tmp[0], tmp[1]);
		else
		{
			head = envs;
			while (envs->next)
				envs = envs->next;
			envs->next = new_envs_node(tmp[0], tmp[1]);
			envs = head;
		}
		splited_free(tmp, 3);
	}
	return (&envs);
}

char	*ft_getenv(t_envs *envs, char *key)
{
	while (envs)
	{
		if (ft_strncmp(envs->key, key, ft_strlen(envs->key)) == 0)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

 char	*expand_env_var(char *buf, t_envs *envs)
{
	int		i;
	char	*result;
	char	**splited_buf;
	char	*tmp;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	splited_buf = ft_split(buf, ' ');
	while (splited_buf[i])
	{
		tmp = ft_strtrim(splited_buf[i], "\"");
		if (tmp[0] == '$')
		{
			result = ft_strjoin(result, " ");
			result = ft_strjoin(result, ft_getenv(envs, tmp + 1));
		}
		else
			result = ft_strjoin(result, splited_buf[i]);
		free(tmp);
		i++;
	}
	splited_free(splited_buf, i);
	return (result);
}
