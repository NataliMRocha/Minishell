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

void	move_redirect(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp && temp->next)
	{
		if (temp && temp->next && temp->type == ARCHIVE
			&& temp->next->type == WORD)
			while (temp && temp->type != WORD)
			{
				move_redirect_right(&temp, &temp->next);
				if (temp->prev)
					temp = temp->prev;
			}
		temp = temp->next;
	}
}
