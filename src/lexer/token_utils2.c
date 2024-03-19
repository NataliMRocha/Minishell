/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:24:43 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/19 11:13:45 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	block_checker(char *str)
{
	if (str[0] == '(' && str[ft_strlen(str) - 1] == ')')
		return (0);
	return (2);
}

int	check_is_directory(t_token **list, char *readline)
{
	int			error;
	struct stat	statbuf;
	char		*tmp;

	statbuf = (struct stat){0};
	if (!(*list)->next)
	{
		tmp = ft_strdup((*list)->data);
		tmp = expand_var(tmp);
		stat(tmp, &statbuf);
		if (ft_strchr(tmp, '/') && S_ISDIR(statbuf.st_mode))
		{
			error = update_status_error(126);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(tmp, STDERR_FILENO);
			ft_putstr_fd(" : ", STDERR_FILENO);
			print_error(error);
			free(readline);
			free_token_list(list);
			free(tmp);
			return (update_status_error(-1));
		}
		free(tmp);
	}
	return (0);
}

int	check_syntax_and_quotes(t_token **list, char *readline)
{
	int	error;

	if (list == NULL || *list == NULL)
		return (0);
	error = check_is_directory(list, readline);
	if (error)
		return (update_status_error(-1));
	error = check_syntax_error(list);
	if (error)
	{
		print_error(error);
		free(readline);
		free_token_list(list);
		return (update_status_error(2));
	}
	error = check_quotes_error(*list);
	if (error)
	{
		print_error(error);
		free(readline);
		free_token_list(list);
		return (update_status_error(2));
	}
	return (0);
}

t_token	*holder_tokens(t_token *tokens, int is_free)
{
	static t_token	*token_address;

	if (tokens && !is_free)
		token_address = tokens;
	if (token_address && is_free)
		free_token_list(&token_address);
	return (token_address);
}
