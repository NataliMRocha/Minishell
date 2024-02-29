/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/29 13:54:24 by egeraldo         ###   ########.fr       */
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

t_envs **create_envs_table(int is_created)
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
	t_envs *envs;

	envs = *create_envs_table(1);
	while (envs)
	{
		if (ft_strncmp(envs->key, key, 125) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

char	*result_var(char *buf,int *i, char *result)
{
	char	*var_name;
	t_envs	*node;

	var_name = ft_strdup("");
	while ((ft_isalnum(buf[*i + 1]) || buf[*i+1] == '?') && buf[++*i])
		var_name = ft_strjoin_char(var_name, buf[*i]);
	node = ft_getenv(var_name);
	if (node)
		result = ft_strjoin(result, ft_getenv(var_name)->value, 1);
	free(var_name);
	return (result);
}

 char	*expand_var(char *buf)
{
	char	*result;
	int		i;
	int		single_quotes;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	single_quotes = ft_handle_quote(buf, '\'');
	while (buf && i < (int)ft_strlen(buf) && buf[i])
	{
		while (single_quotes-- > 0)
			result = ft_strjoin_char(result, buf[i++]);
		if (buf[i] == '$')
			result = result_var(buf, &i, result);
		else
			result = ft_strjoin_char(result, buf[i]);
		i++;
	}
	return (result);
}
