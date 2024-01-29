/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/29 17:56:36 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_token *token_list = NULL;
	t_token *temp;

	while (1)
	{
		char *test = ft_readline();
		list_fill(&token_list, test);
		if (check_syntax_error(&token_list) || check_quotes_error(token_list))
			ft_putendl_fd("Syntax error", 2);
		temp = token_list;
		while(temp)
		{
			if (temp->data == NULL)
				break;
			printf("data: %s  \t  type: %d\n", temp->data, temp->type);
			temp = temp->next;
		}
		free(test);
		free_list(token_list);
		token_list = NULL;
	}
}
