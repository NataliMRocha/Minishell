/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 12:33:40 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_status_error(int i)
{
	static int status;

	if (i == -1)
		return (status);
	status = i;
	return (status);
}

void	free_program(t_ast **root, char **get_cmd, t_envs **var_envs)
{
	if (get_cmd && *get_cmd)
		free(*get_cmd);
	if (root && *root)
	{
		free_ast(*root, 0);
		*root = NULL;
	}
	if (var_envs && *var_envs)
		free_env_list(*var_envs);
}

void	capture_heredoc(t_token *token_list)
{
	t_token	*temp;
	char	count;

	temp = token_list;
	count = 'A';
	while (temp)
	{
		if (temp->type == HEREDOC)
			heredoc(temp->next->data, count++);
		temp = temp->next;
	}
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
		if (ft_strncmp(get_cmd, "exit", 4) == 0)
			break;
		if ((get_cmd && !*get_cmd) || list_fill(&token_list, get_cmd) != 0)
			continue;
		capture_heredoc(token_list);
		if (check_syntax_and_quotes(&token_list, get_cmd))
			continue;
		root = parser(token_list);
		starting_exec(root);
		free_program(&root, &get_cmd, NULL);
		token_list = NULL;
	}
	free_program(&root, &get_cmd, var_envs);
	close_fds(NULL, 1);
	return (0);
}
