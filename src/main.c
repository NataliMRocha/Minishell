/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/26 18:10:02 by egeraldo         ###   ########.fr       */
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

/* int main(void)
{
	char **paths = ft_split(getenv("USER"), ':');
	 char *args[] = {"touch", "oi(oi)", NULL};
	execve("/usr/bin/touch", args, NULL);
	printf("%s\n", *paths);
}
*/