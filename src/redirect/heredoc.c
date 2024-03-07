/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:47:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 16:19:29 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	filling_archive(char *delim, int fd)
{
	char	*temp;
	char	*buf;

	while (1)
	{
		// write(1, "$>", 2);
		buf = readline("$> ");
		if (ft_strncmp(buf, delim, ft_strlen(delim)) == 0)
		{
			ft_putstr_fd("\n", fd);
			free(buf);
			break ;
		}
		if (ft_strchr(buf, '$') && !ft_handle_quote(delim, 0, 1))
		{
			temp = expand_var(buf);
			ft_putstr_fd(temp, fd);
			free(temp);
		}
		else
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
