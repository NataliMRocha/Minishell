/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:22:00 by natali            #+#    #+#             */
/*   Updated: 2024/03/18 20:28:58 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_duplicated_symbol(t_token *tmp)
{
	char	*c1;
	char	*c2;

	if (!tmp || !tmp->data)
		return (0);
	c1 = tmp->data;
	c2 = "";
	if (tmp->type == HEREDOC && !tmp->next)
		return (1);
	if (tmp->next && is_symbol(tmp->next->data))
		c2 = tmp->next->data;
	return (c1[0] == c2[0]);
}

int	check_syntax_error(t_token **list)
{
	t_token	*tmp;

	if (list == NULL || *list == NULL)
		return (0);
	tmp = *list;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR
		|| (tmp->type > 4 && tmp->next == NULL))
		return (tmp->type);
	while (tmp || (tmp && tmp->next))
	{
		if (is_redir_followed_by_pipe(tmp))
			return (PIPE);
		if (is_duplicated_symbol(tmp))
			return (tmp->type);
		if (check_block_error(tmp))
			return (2);
		if (is_redir_after_symbol(tmp))
			return (tmp->next->type);
		if (check_quotes_error(tmp))
			return (1);
		tmp = tmp->next;
		if (tmp && tmp->type > 4 && tmp->next == NULL)
			return (13);
	}
	return (0);
}

int	check_quotes_error(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->data[0] == *"'" || list->data[0] == '"')
		{
			i = ft_handle_quote(list->data, list->data[0], 1);
			if (i == 0)
				return (1);
		}
		list = list->next;
	}
	return (0);
}
