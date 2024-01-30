/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:22:00 by natali            #+#    #+#             */
/*   Updated: 2024/01/30 11:57:59 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_followed_by_pipe(t_token *tmp)
{
	return ((tmp->type == REDIR_IN && tmp->next->type == PIPE)
		|| (tmp->type == REDIR_OUT && tmp->next->type == PIPE));
}

int	is_duplicated_symbol(t_token *tmp)
{
	char c1;
    char c2;

	c1 = tmp->data[0];
	c2 = 0;
	if (is_symbol(c1) && (ft_strlen(tmp->data) > 2))
		return (1);
	if (tmp->next && is_symbol(tmp->next->data[0]))
		c2 = tmp->next->data[0];
    return (c1 == c2);
}

int	check_syntax_error(t_token **list)
{
	t_token	*tmp;

	if (list == NULL || *list == NULL)
		return (0);
	tmp = *list;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
		return (1);
	while (tmp->next)
	{
		if (is_redir_followed_by_pipe(tmp))
			return (1);
		if (is_duplicated_symbol(tmp))
			return (1);
		tmp = tmp->next;
	}
	if (tmp->type > 3 && tmp->next == NULL)
		return (1);
	return (0);
}

int	check_quotes_error(t_token *list)
{
	int i;

	i = 0;
	while (list)
	{
		if (list->data[0] == *"'" || list->data[0] == '"')
		{
			i = ft_handle_quote(list->data, list->data[0]);
			if (i == 0)
				return (1);
		}
		list = list->next;
	}
	return (0);
}