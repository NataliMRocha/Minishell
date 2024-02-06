/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:41:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/06 11:33:04 by egeraldo         ###   ########.fr       */
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

int	list_fill(t_token **list, char *readline, t_envs *var_envs)
{
	char	*token;
	int		call;
	t_envs	*node;

	call = 0;
	token = " ";
	while (token && *token != '\0')
	{
		token = ft_strtok(readline, call++);
		if (token && *token != '\0')
			append_node(list, token);
	}
	if (!*list || check_syntax_error(list) || check_quotes_error(*list))
	{
			printf("Syntax Error\n");
			free(readline);
			free_token_list(*list);
			free(token);
			node = ft_getenv(var_envs, "?");
			free(node->value);
			node->value = ft_strdup("2");
			return(2);
	}
	return (0);
}
