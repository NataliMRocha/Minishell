/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 18:49:21 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_token *token_list = NULL;
	t_token *temp;
	t_envs **var_envs = create_envs_table();
	char *get_cmd;
	// setup_signals();

	while (1)
	{
		get_cmd = ft_readline();
		// heredoc("result_heredoc", "eof", *var_envs);
		list_fill(&token_list, get_cmd);
		temp = token_list;
		if (ft_strncmp("export", token_list->data, ft_strlen(token_list->data)) == 0)
			ft_export(temp->next->data, var_envs);
		else if (ft_strncmp("unset", token_list->data, ft_strlen(token_list->data)) == 0)
			ft_unset(temp->next->data, var_envs);
		else if (ft_strncmp("env", token_list->data, ft_strlen(token_list->data)) == 0)
			print_env_list(*var_envs);
		else if (ft_strncmp("exit", token_list->data, ft_strlen(token_list->data)) == 0)
			break ;
		printf("\n-------------------------------------------------------------\n");
		while(temp)
		{
			if (temp->data == NULL)
				break;
			char *chatao = expand_env_var(temp->data, *var_envs);
			printf("data: %s  \t  type: %d\n", chatao, temp->type);
			temp = temp->next;
			free(chatao);
		}
		printf("\n-------------------------------------------------------------\n");
		free(get_cmd);
		free_token_list(token_list);
		token_list = NULL;
	}
	free(get_cmd);
	free_token_list(token_list);
	free_env_list(*var_envs);
}
