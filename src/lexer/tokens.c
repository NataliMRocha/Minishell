/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:41:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/29 17:49:40 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_write_types(t_token *list)
{
	if (list->data[0] == '|' && list->data[1] == '|')
		return ((void)(list->type = OR));
	if (list->data[0] == '&' && list->data[1] == '&')
		return ((void)(list->type = AND));
	if (list->data[0] == '>' && list->data[1] == '>')
		return ((void)(list->type = REDIR_APPEND));
	if (list->data[0] == '<' && list->data[1] == '<')
		return ((void)(list->type = REDIR_HERE_DOC));
	if (list->data[0] == '|')
		return ((void)(list->type = PIPE));
	if (list->data[0] == '>')
		return ((void)(list->type = REDIR_OUT));
	if (list->data[0] == '<')
		return ((void)(list->type = REDIR_IN));
	if (list->data[0] == '"')
		return ((void)(list->type = DQUOTE));
	if (list->data[0] == '\'')
		return ((void)(list->type = QUOTE));
	if (list->data[0] == '(')
		return ((void)(list->type = PAREN_OPEN));
	if (list->data[0] == ')')
		return ((void)(list->type = PAREN_CLOSE));
}

void	list_fill(t_token **list, char *readline)
{
	char	*token;
	int		call;

	call = 0;
	token = " ";
	while (token && *token != '\0')
	{
		token = ft_strtok(readline, call++);
		if (token && *token != '\0')
			append_node(list, token);
	}
}
