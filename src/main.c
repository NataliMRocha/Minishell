/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/15 13:34:35 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_token *token_list = NULL;
	t_token *temp;
	t_envs **var_envs = create_envs_table();
	char *get_cmd;
	//setup_signals();

	while (1)
	{
		get_cmd = ft_readline();
		// heredoc("result_heredoc", "eof", *var_envs);
		if (list_fill(&token_list, get_cmd, *var_envs) != 0)
			continue;
		if (parser(&token_list, var_envs) == 3)
			break;
		temp = token_list;
		printf("\n-------------------------------------------------------------\n");
		while(temp)
		{
			if (temp->data == NULL)
				break;
			printf("data: %s  \t  type: %d\n", temp->data, temp->type);
			temp = temp->next;
		}
		printf("\n-------------------------------------------------------------\n");
		free(get_cmd);
		free_token_list(token_list);
		token_list = NULL;
	}
	free(get_cmd);
	free_token_list(token_list);
	free_env_list(*var_envs);
	return (0);
}
