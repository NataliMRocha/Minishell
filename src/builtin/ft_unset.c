/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:06:17 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 17:35:57 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **keys)
{
	t_envs	*temp;
	t_envs	*free_node;
	int		i;

	temp = *create_envs_table(1);
	free_node = NULL;
	while (temp && temp->next)
	{
		i = -1;
		while (keys && keys[++i])
		{
			if (ft_strcmp(temp->next->key, keys[i]) == 0)
			{
				free_node = temp->next;
				free(temp->next->key);
				free(temp->next->value);
				temp->next = temp->next->next;
				free(free_node);
			}
		}
		temp = temp->next;
	}
	return (update_status_error(0));
}

int	print_env_list(t_envs *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
	return (update_status_error(0));
}
