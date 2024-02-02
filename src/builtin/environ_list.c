/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:17:03 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 12:52:05 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char *key, t_envs **var_envs)
{
	t_envs	*temp;

	temp = *var_envs;
	while (temp->next)
	{
		if (ft_strncmp(temp->next->key, key, ft_strlen(temp->next->key)) == 0)
		{
			free(temp->next->key);
			free(temp->next->value);
			temp->next = temp->next->next;
			break ;
		}
		temp = temp->next;
	}
}

void	ft_export(char *variable, t_envs **var_envs)
{
	t_envs	*temp;
	t_envs	*new_node;
	char	*key;
	char	*value;

	temp = *var_envs;
	while (temp->next->next)
		temp = temp->next;
	if (strchr(variable, '='))
	{
		key = ft_strcpy_delim(variable, '=');
		value = ft_strchr(variable, '=') + 1;
		new_node = ft_getenv(*var_envs, key);
		if (new_node)
		{
			free(new_node->value);
			new_node->value = ft_strdup(value);
		}
		else
			temp->next->next = new_envs_node(key, value);
	}
}
