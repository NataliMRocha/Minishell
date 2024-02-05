/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/05 22:16:24 by codespace        ###   ########.fr       */
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
		temp = token_list;
		if (token_list && ft_strncmp("export", token_list->data, ft_strlen(token_list->data)) == 0)
			ft_export(temp->next->data, var_envs);
		else if (token_list && ft_strncmp("unset", token_list->data, ft_strlen(token_list->data)) == 0)
			ft_unset(temp->next->data, var_envs);
		else if (token_list && ft_strncmp("env", token_list->data, ft_strlen(token_list->data)) == 0)
			print_env_list(*var_envs);
		else if (token_list && ft_strncmp("exit", token_list->data, ft_strlen(token_list->data)) == 0)
			break ;
		printf("\n-------------------------------------------------------------\n");
		while(temp)
		{
			if (temp->data == NULL)
				break;
			char *chatao = expand_env_var(temp->data, *var_envs);
			chatao = ft_remove_quotes(chatao);
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
	return (0);
}
