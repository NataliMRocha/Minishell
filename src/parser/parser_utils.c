/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:04:56 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/15 13:47:34 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	splited_free(char **str, int words_len)
{
	while (words_len-- > 0)
		free(str[words_len]);
	free(str);
}

void	free_env_list(t_envs *list)
{
	t_envs	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}
}

int	update_status_error(t_envs *var_envs, char *status)
{
	t_envs	*node;

	node = ft_getenv(var_envs, "?");
	free(node->value);
	node->value = ft_strdup(status);
	return (ft_atoi(status));
}
