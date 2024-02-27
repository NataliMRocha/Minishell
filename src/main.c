/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/27 17:35:55 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_status_error(int i)
{
	int static	status;


	if (i == -1)
		return (status);
	status = i;
	return (status);
}

void	free_program(t_ast **root, t_token **token_list, char **get_cmd, t_envs **var_envs)
{
	if (get_cmd && *get_cmd)
		free(*get_cmd);
	if (root && *root)
	{
		free_ast(*root);
		*root = NULL;
	}
	if (token_list && *token_list)
	{
		free_token_list(*token_list);
		*token_list = NULL;
	}
	if (var_envs && *var_envs)
		free_env_list(*var_envs);
}

int main(void)
{
	t_token *token_list = NULL;
	t_ast	*root;
	char *get_cmd;
	//setup_signals();

	t_envs **var_envs = create_envs_table(0);
	root = NULL;
	while (1)
	{
		get_cmd = ft_readline();
		// heredoc("result_heredoc", "eof", *var_envs);
		if (ft_strncmp(get_cmd, "exit", 4) == 0)
			break;
		if (list_fill(&token_list, get_cmd) != 0)
			continue;
		root = parser(token_list);
		starting_exec(root);
		free_program(&root, &token_list, &get_cmd, NULL);
	}
	free_program(&root, &token_list, &get_cmd, var_envs);
	return (0);
}
