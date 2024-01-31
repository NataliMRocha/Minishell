/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:01:00 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/30 19:16:44 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* char	*expand_env_var(char *buf)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(buf) + 1));
	while (buf[i])
	{
		result[i] = buf[i];
		if (buf[i] == '$')
		{
			j = 1;
			while (buf[i + j] && buf[i + j] != ' ')
				j++;
			ft_strlcpy(result, &buf[i + 1], j);
			return (result);
		}
		i++;
	}
} */

int    heredoc(char *delim)
{
    char	*buf;
    int		fd;
	char	*temp;

    fd = open(delim, O_CREAT | O_WRONLY | O_APPEND, 0000644);
    if (fd < 0)
        return (ft_putendl_fd("heredoc: archive not open", 2));
    while (1)
    {
        printf("\001\x1b[38;2;252;127;0m\002$>\001\x1b[25;0m\002");
        buf = get_next_line(0);
        if (ft_strncmp(buf, delim, ft_strlen(delim)) == 0)
            break ;
		if (ft_strchr(buf, '$'))
		{
			temp = expand_env_var(buf);
        	ft_putstr_fd(temp, fd);
			free(temp);
		}
		else
        	ft_putstr_fd(buf, fd);
		free(buf);
    }
    return (fd);
}
