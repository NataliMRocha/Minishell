/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:47:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/14 20:39:29 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void close_heredoc(int std_in, int fd)
{
	if (g_last_signal == SIGINT)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
	close(fd);
	close (std_in);
}

int	filling_archive(char *delim, int fd, int std_in)
{
	char	*buf;
	char	*no_quotes;

	no_quotes = ft_remove_quotes(delim);
	on_heredoc(1);
	buf = readline("$> ");
	on_heredoc(0);
	if (g_last_signal == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		if (buf)
		{
			free (buf);
			buf = NULL;
		}
	}
	if (!buf || !ft_strncmp(buf, no_quotes, ft_strlen(no_quotes)))
	{
		ft_putstr_fd("\n", fd);
		free(no_quotes);
		if (buf)
			free(buf);
		return(0);
	}
	if (ft_strchr(buf, '$') && !ft_handle_quote(delim, 0, 1))
		buf = expand_var(buf);
	ft_putstr_fd(buf, fd);
	free(buf);
	free(no_quotes);
	buf = NULL;
	return(1);
}

int	heredoc(char **delim, char count)
{
	int		fd;
	char	*name;
	char	*temp;
	const int	std_in = dup(STDIN_FILENO);

	name = ft_strcpy_delim(*delim, 0);
	temp = ft_strjoin_char(name, count);
	name = ft_strjoin("/tmp/", temp, 0);
	free(temp);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (ft_putendl_fd("heredoc: archive not open", 2));
	while (filling_archive(*delim, fd, std_in))
		;
	close_heredoc(std_in, fd);
	free(*delim);
	*delim = NULL;
	*delim = strdup(name);
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
