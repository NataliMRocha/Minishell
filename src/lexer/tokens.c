/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:41:05 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/29 13:30:57 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_write_types(t_token *list)
{
	if(list->data[0] == '|' && list->data[1] == '|')
		list->type = OR;
	else if(list->data[0] == '&' && list->data[1] == '&')
		list->type = AND;
	else if(list->data[0] == '>' && list->data[1] == '>')
		list->type = REDIR_APPEND;
	else if(list->data[0] == '<' && list->data[1] == '<')
		list->type = REDIR_HERE_DOC;
	else if(list->data[0] == '|')
		list->type = PIPE;
	else if(list->data[0] == '>')
		list->type = REDIR_OUT;
	else if(list->data[0] == '<')
		list->type = REDIR_IN;
	else if(list->data[0] == '"')
		list->type = DQUOTE;
	else if(list->data[0] == '\'')
		list->type = QUOTE;
	else if(list->data[0] == '(')
		list->type = PAREN_OPEN;
	else if(list->data[0] == ')')
		list->type = PAREN_CLOSE;
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
		if (token)
			append_node(list, token);
	}
	if (check_syntaxe(list))
		ft_putendl_fd("syntax error DOIS", 2);
	
}
