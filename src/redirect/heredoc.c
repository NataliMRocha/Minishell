/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:47:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 12:41:09 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void filling_archive(char *delim, int fd)
{
    char    *temp;
    char    *buf;

    while (1)
	{
		write(1, "$>", 2);
		buf = get_next_line(0);
		if (ft_strncmp(buf, delim, ft_strlen(delim)) == 0)
			break ;
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

int	heredoc(char *delim, char count)
{
	int		fd;
	char	*name;

    name = ft_strtrim(delim, "");
	name = ft_strjoin("/tmp/", ft_strjoin_char(name, count), 0);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (ft_putendl_fd("heredoc: archive not open", 2));
	filling_archive(delim, fd);
    free(delim);
    delim = strdup(name);
	close(fd);
	free(name);
	return (fd);
}
