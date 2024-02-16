/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:47:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/16 10:48:52 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    heredoc(char *name, char *delim, t_envs *var_envs)
{
    char	*buf;
    int		fd;
	char	*temp;

    fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777);
    if (fd < 0)
        return (ft_putendl_fd("heredoc: archive not open", 2));
    while (1)
    {
        write(1, "$>", 2);
        buf = get_next_line(0);
        if (ft_strncmp(buf, delim, ft_strlen(delim)) == 0)
            break ;
		if (ft_strchr(buf, '$'))
		{
			temp = expand_var(buf, var_envs);
        	ft_putstr_fd(temp, fd);
			free(temp);
		}
		else
        	ft_putstr_fd(buf, fd);
		free(buf);
    }
    return (fd);
}