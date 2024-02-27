/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:04:56 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/27 16:32:35 by egeraldo         ###   ########.fr       */
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

int	is_redirect(t_token *token)
{
	if (token && (token->type == REDIR_OUT || token->type == REDIR_APPEND
			|| token->type == REDIR_IN || token->type == HEREDOC))
		return (1);
	return (0);
}
