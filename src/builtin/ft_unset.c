/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:06:17 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/08 18:07:25 by egeraldo         ###   ########.fr       */
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

void	print_env_list(t_envs *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
}
