/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/29 19:29:39 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_name(char *buf)
{
	int		i;
	int		j;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	while (buf[i])
	{
		if (buf[i] == '$')
		{
			j = 1;
			while (buf[i + j] && buf[i + j] != ' ')
				j++;
			temp = ft_substr(buf, i + 1, j);
			result = ft_strjoin(result, getenv(temp)); //vazamento de memoria
			free(temp);
			i += j;
		}
		else
			result = ft_strjoin(result, ft_memcpy(temp, (void *)&buf[i], 1));
		i++;
	}
	return (result);
}

char	*expand_env_var(char *buf)
{
	char	*result;

	result = var_name(buf);
	printf("%s", result);

	return (result);
}