/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:24:43 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/15 10:39:25 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	block_checker(char *str)
{
	int	is_corret;
	int	i;

	i = 0;
	is_corret = 0;
	if (str && str[i++] == '(')
		while (str && str[i] && str[i] != ')')
			if(ft_isalnum(str[i++]))
				is_corret = 2;
	if (i == 1 && str[i] == ')')
		is_corret = 2;
	return (is_corret);
}

int	check_is_directory(t_token **list, char *readline)
{
	int			error;
	struct stat	statbuf;

	statbuf = (struct stat){0};
	if (!(*list)->next)
	{
		(*list)->data = expand_var((*list)->data);
		stat((*list)->data, &statbuf);
		if (ft_strchr((*list)->data, '/') && S_ISDIR(statbuf.st_mode))
		{
			error = update_status_error(126);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd((*list)->data, STDERR_FILENO);
			ft_putstr_fd(" : ", STDERR_FILENO);
			print_error(error);
			free(readline);
			free_token_list(list);
			return (update_status_error(-1));
		}
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
