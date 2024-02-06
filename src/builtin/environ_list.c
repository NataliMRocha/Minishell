/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:17:03 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/06 11:43:30 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char *key, t_envs **envs)
{
	t_envs	*temp;
	t_envs	*free_node;

	temp = *envs;
	free_node = NULL;
	while (temp->next)
	{
		if (ft_strncmp(temp->next->key, key, ft_strlen(temp->next->key)) == 0)
		{
			free_node = temp->next;
			free(temp->next->key);
			free(temp->next->value);
			temp->next = temp->next->next;
			free(free_node);
			break ;
		}
		temp = temp->next;
	}
}

// TODO: bloquear a edição a variavel "?" pelo usuario
void	ft_export(char *var, t_envs **envs)
{
	t_envs	*temp;
	t_envs	*new_node;
	char	*key;
	char	*value;

	temp = *envs;
	while (temp->next->next)
		temp = temp->next;
	if (strchr(var, '='))
	{
		key = ft_strcpy_delim(var, '=');
		value = ft_remove_quotes(expand_var(ft_strchr(var, '=') + 1, *envs));
		new_node = ft_getenv(*envs, key);
		if (new_node)
		{
			free(new_node->value);
			new_node->value = ft_strdup(value);
		}
		else
			temp->next->next = new_envs_node(key, value);
		free(key);
		free(value);
	}
}

void	print_env_list(t_envs *envs)
{
	while (envs)
	{
		if (envs->key[0] == '?')
		{
			envs = envs->next;
			continue ;
		}
		printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
}