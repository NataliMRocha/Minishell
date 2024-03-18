/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:47:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 18:08:31 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_heredoc(int std_in, int fd, int in_filling)
{
	if (g_last_signal != SIGINT && in_filling)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
	close(fd);
	close(std_in);
}

void	handle_buf(char *buf, int std_in)
{
	if (g_last_signal == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
	}
}

void	filling_archive(char *delim, int fd, int std_in)
{
	char	*buf;
	char	*no_quotes;

	no_quotes = ft_remove_quotes(delim);
	while (1)
	{
		buf = readline("$> ");
		handle_buf(buf, std_in);
		if (!buf || (buf && ft_strncmp(buf, no_quotes,
					ft_strlen(no_quotes)) == 0))
		{
			free(no_quotes);
			if (buf)
				on_heredoc(0);
			free(buf);
			buf = NULL;
			break ;
		}
		if (buf && ft_strchr(buf, '$') && !ft_handle_quote(delim, 0, 1))
			buf = expand_var(buf);
		ft_putendl_fd(buf, fd);
		free(buf);
	}
}

int	heredoc(char **delim, char count)
{
	int			fd;
	char		*name;
	char		*temp;
	const int	std_in = dup(STDIN_FILENO);

	name = ft_strcpy_delim(ft_remove_quotes(*delim), 0);
	temp = ft_strjoin_char(name, count);
	name = ft_strjoin("/tmp/", temp, 0);
	free(temp);
	on_heredoc(1);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (ft_putendl_fd("heredoc: archive not open", 2));
	filling_archive(*delim, fd, std_in);
	free(*delim);
	*delim = NULL;
	*delim = strdup(name);
	close_heredoc(fd, std_in, on_heredoc(-1));
	on_heredoc(0);
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
