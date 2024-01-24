/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/24 14:46:10 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_token *token_list = NULL;

	while (1)
	{
		char *test = ft_readline();
		list_fill(&token_list, test);
		while(token_list)
		{
			printf("data: %s\n", token_list->data);
			printf("type: %d\n", token_list->type);
			token_list = token_list->next;
		}
	}
}