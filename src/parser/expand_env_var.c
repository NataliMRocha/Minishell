/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/05 21:06:04 by codespace        ###   ########.fr       */
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
		splited_free(tmp, 2);
	}
	return (&envs);
}

t_envs	*ft_getenv(t_envs *envs, char *key)
{
	while (envs)
	{
		if (ft_strncmp(envs->key, key, 125) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

 char	*expand_env_var(char *buf, t_envs *envs)
{
	char	*result;
	char	*var_name;
	int		i;
	int		single_quotes;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	single_quotes = ft_handle_quote(buf, '\'');
	while (buf && i < (int)ft_strlen(buf) && buf[i])
	{
		while (single_quotes-- > 0)
			result = ft_strjoin(result, ft_chartostr(buf[i++]));
		if (buf[i] == '$')
		{
			var_name = ft_strdup("");
			while (ft_isalnum(buf[i + 1]) && buf[++i])
				var_name = ft_strjoin(var_name, ft_chartostr(buf[i]));
			result = ft_strjoin(result, ft_getenv(envs, var_name)->value);
			free(var_name);
		}
		else
			result = ft_strjoin(result, ft_chartostr(buf[i]));
		i++;
	}
	return (result);
}
