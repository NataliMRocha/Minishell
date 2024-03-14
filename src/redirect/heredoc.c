/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:47:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/14 17:58:47 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	filling_archive(char *delim, int fd)
{
	char	*buf;
	char	*no_quotes;

	no_quotes = ft_remove_quotes(delim);
	while (1)
	{
		on_heredoc(1);
		buf = readline("$> ");
		on_heredoc(0);
		if (ft_strncmp(buf, no_quotes, ft_strlen(no_quotes)) == 0)
		{
			ft_putstr_fd("\n", fd);
			free(buf);
			free(no_quotes);
			break ;
		}
		if (ft_strchr(buf, '$') && !ft_handle_quote(delim, 0, 1))
			buf = expand_var(buf);
		ft_putstr_fd(buf, fd);
		free(buf);
	}
}

int	heredoc(char **delim, char count)
{
	int		fd;
	char	*name;
	char	*temp;

	name = ft_strcpy_delim(*delim, 0);
	temp = ft_strjoin_char(name, count);
	name = ft_strjoin("/tmp/", temp, 0);
	free(temp);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (ft_putendl_fd("heredoc: archive not open", 2));
	filling_archive(*delim, fd);
	free(*delim);
	*delim = NULL;
	*delim = strdup(name);
	close(fd);
	free(name);
	return (fd);
}

void	capture_heredoc(t_token **token_list)
{
	t_token	*temp;
	char	count;

	temp = *token_list;
	count = 'A';
	while (temp)
	{
		if (temp->type == HEREDOC)
			heredoc(&temp->next->data, count++);
		temp = temp->next;
	}
}
