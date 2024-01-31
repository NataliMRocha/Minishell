/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/31 17:35:38 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	t_token *token_list = NULL;
	t_token *temp;
	t_envs **var_envs = create_envs_table();

	while (1)
	{
		char *get_cmd = ft_readline();
		heredoc("/nfs/homes/egeraldo/nave/minishell/HEREDOC", "eof", *var_envs);
		list_fill(&token_list, get_cmd);
		if (check_syntax_error(&token_list) || check_quotes_error(token_list))
			ft_putendl_fd("Syntax error", 2);
		temp = token_list;
		while(temp)
		{
			if (temp->data == NULL)
				break;
			char *chatao = expand_env_var(temp->data, *var_envs);
			printf("data: %s  \t  type: %d\n", chatao, temp->type);
			temp = temp->next;
			free(chatao);
		}
		free(get_cmd);
		free_token_list(token_list);
		token_list = NULL;
	}
	free_env_list(*var_envs);
}
