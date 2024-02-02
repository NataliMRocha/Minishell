/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 12:51:13 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_token *token_list = NULL;
	t_token *temp;
	t_envs **var_envs = create_envs_table();
	t_envs *envs;
	setup_signals();

	while (1)
	{
		char *get_cmd = ft_readline();
		// heredoc("result_heredoc", "eof", *var_envs);
		list_fill(&token_list, get_cmd);
		if (check_syntax_error(&token_list) || check_quotes_error(token_list))
			ft_putendl_fd("Syntax error", 2);
		temp = token_list;
		if (ft_strncmp("export", token_list->data, ft_strlen(token_list->data)) == 0)
			ft_export(temp->next->data, var_envs);
		else if (ft_strncmp("unset", token_list->data, ft_strlen(token_list->data)) == 0)
			ft_unset(temp->next->data, var_envs);
		envs = *var_envs;
		while (envs)
		{
			printf("key: %s  \t  value: %s\n", envs->key, envs->value);
			envs = envs->next;
		}
		/* while(temp)
		{
			if (temp->data == NULL)
				break;
			char *chatao = expand_env_var(temp->data, *var_envs);
			printf("data: %s  \t  type: %d\n", chatao, temp->type);
			temp = temp->next;
			free(chatao);
		} */
		free(get_cmd);
		free_token_list(token_list);
		token_list = NULL;
	}
	free_env_list(*var_envs);
}
