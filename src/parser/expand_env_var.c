/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/30 11:33:28 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	splited_free(char **s, size_t w)
{
	while (w-- > 0)
		free(s[w]);
	free(s);
}

char	*expand_env_var(char *buf)
{
	int		i;
	char	*result;
	char	**splited_buf;
	char	*tmp;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	splited_buf = ft_split(buf, ' ');
	while (splited_buf[i])
	{
		tmp = ft_strtrim(splited_buf[i], "\"");
		if (tmp[0] == '$')
		{
			result = ft_strjoin(result, getenv(tmp + 1));
			result = ft_strjoin(result, " ");
		}
		free(tmp);
		i++;
	}
	splited_free(splited_buf, i);
	return (result);
}
