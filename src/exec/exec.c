/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:08:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/29 17:15:19 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expanded_variable(t_ast **root)
{
	int	i;
	char **expanded;

	i = -1;
	expanded = NULL;
	while (root && (*root)->command_list[++i])
		(*root)->command_list[i] = expand_var((*root)->command_list[i]);
	i = 0;
	if (root && !*(*root)->command_list[i])
	{
		expanded = ft_calloc(i, sizeof(char *));
		while((*root)->command_list[++i])
			expanded[i - 1] = ft_strdup((*root)->command_list[i]);
		free_split((*root)->command_list);
		(*root)->command_list = NULL;
		return (expanded);
	}
	return ((*root)->command_list);
}

void	exec(t_ast *root)
{
	char	*path;
	int		status;
	pid_t	i;

	status = update_status_error(-1);
	root->command_list = expanded_variable(&root);
	path = verify_path(root);
	i = fork();
	if (i == 0 && root->type == EXEC)
	{
		if (execve(path, &root->command_list[i], NULL) < 0)
		{
			ft_putstr_fd("command not found: ", STDERR_FILENO);
			ft_putstr_fd(root->command_list[0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			root = ast_holder(NULL, 1);
			free_program(&root, &path, create_envs_table(1));
			close_fds(NULL, 1);
			exit(update_status_error(127));
		}
	}
	wait(&status);
	free(path);
	update_status_error(status);
}

void handle_and_or(t_ast *root)
{
	int status_code;

	starting_exec(root->left);
	status_code = update_status_error(-1);
	if((!status_code) && root->type == AND)
		starting_exec(root->right);
	else if (status_code && root->type == OR)
		starting_exec(root->right);
}

void starting_exec(t_ast *root)
{
	if(root->type == AND || root->type == OR)
		handle_and_or(root);
	else if (root->type == PIPE)
		handle_pipe(root);
	else if(root->left)
		starting_exec(root->left);
	else if(root->right)
		starting_exec(root->right);
	else if(root)
		exec(root);
}