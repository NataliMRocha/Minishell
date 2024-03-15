/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:22:00 by natali            #+#    #+#             */
/*   Updated: 2024/03/15 10:46:11 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_followed_by_pipe(t_token *tmp)
{
	return (tmp && ((tmp->type == REDIR_IN && tmp->next->type == PIPE)
			|| (tmp->type == REDIR_OUT && tmp->next->type == PIPE)));
}

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

int	check_block_error(t_token *list)
{
	return (list && ((list->type == BLOCK && block_checker(list->data))
			|| (list->type == BLOCK && list->prev
				&& is_redirect(list->prev->type))));
}

int	check_syntax_error(t_token **list)
{
	t_token	*tmp;

	if (list == NULL || *list == NULL)
		return (0);
	tmp = *list;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
		return (tmp->type);
	while (tmp || (tmp && tmp->next))
	{
		if (is_redir_followed_by_pipe(tmp))
			return (PIPE);
		if (is_duplicated_symbol(tmp))
			return (tmp->type);
		if (check_block_error(tmp))
			return (2);
		if (tmp && (tmp->data && is_symbol(tmp->data) && (tmp->next
					&& is_symbol(tmp->next->data))
				&& !is_redirect(tmp->next->type)))
			return (tmp->next->type);
		if (check_quotes_error(tmp))
			return (1);
		tmp = tmp->next;
	}
	if (tmp && tmp->type > 4 && tmp->next == NULL)
		return (13);
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
