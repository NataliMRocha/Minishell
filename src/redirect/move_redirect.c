/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:38 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/23 10:05:23 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	move_redirect_right(t_token **arch, t_token **word)
{
	char	*file_name;
	int		type;

	file_name = (*arch)->data;
	type = (*arch)->type;
	(*arch)->data = (*word)->data;
	(*arch)->type = (*word)->type;
	(*word)->data = file_name;
	(*word)->type = type;
}

int	is_move(t_token *temp)
{
	return (temp->next->type == WORD || temp->next->type == QUOTE
		|| temp->next->type == DQUOTE);
}

void	move_redirect(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp && temp->next)
	{
		if (temp && temp->next && temp->type == ARCHIVE && is_move(temp))
		{
			while (temp && (temp->type == ARCHIVE || is_redirect(temp->type)))
			{
				move_redirect_right(&temp, &temp->next);
				if (temp->prev)
					temp = temp->prev;
			}
		}
		temp = temp->next;
	}
}

int	is_directory(char *name)
{
	struct stat	statbuf;
	char		*tmp;

	statbuf = (struct stat){0};
	tmp = ft_strdup(name);
	tmp = expand_var(tmp);
	stat(tmp, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		free(tmp);
		return (update_status_error(1));
	}
	free(tmp);
	return (0);
}
