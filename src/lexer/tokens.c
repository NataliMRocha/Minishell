/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:41:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/06 17:17:17 by egeraldo         ###   ########.fr       */
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
		return ((void)(list->type = HEREDOC));
	if (list->data[0] == '|')
		return ((void)(list->type = PIPE));
	if (list->data[0] == '>')
		return ((void)(list->type = REDIR_OUT));
	if (list->data[0] == '<')
		return ((void)(list->type = REDIR_IN));
	if (list->data[0] == '"' && !is_redirect(list->prev))
		return ((void)(list->type = DQUOTE));
	if (list->data[0] == '\'' && !is_redirect(list->prev))
		return ((void)(list->type = QUOTE));
	if (list->data[0] == '(')
		return ((void)(list->type = BLOCK));
	if (is_redirect(list->prev) && list->type == WORD)
		return ((void)(list->type = ARCHIVE));
}

void	stack_fill(t_token *list)
{
	list->data = "";
	list->type = 0;
	list->next = NULL;
	list->prev = NULL;
}

void	append_node(t_token **list, char *content)
{
	t_token	*node;
	t_token	*last_node;

	if (list == NULL)
		return ;
	node = malloc(sizeof(t_token));
	if (node == NULL)
		return ;
	stack_fill(node);
	node->next = NULL;
	node->data = content;
	if (*list == NULL || (*list)->data == NULL)
	{
		*list = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*list);
		last_node->next = node;
		node->prev = last_node;
	}
	ft_write_types(node);
}

t_token	**get_tokens(t_token *tokens)
{
	static t_token	*list;

	if (tokens)
		list = tokens;
	return (&list);
}

int	list_fill(t_token **list, char *readline)
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
	if (*list && (check_syntax_error(list) || check_quotes_error(*list)))
	{
		printf("Syntax Error\n");
		free(readline);
		free_token_list(list);
		*list = NULL;
		list = NULL;
		free(token);
		return (update_status_error(2));
	}
	get_tokens(*list);
	return (0);
}
