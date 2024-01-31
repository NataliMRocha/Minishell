/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/30 19:16:58 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envs **envs(void)
{
	static t_envs	**envs;
	int				i;

	i = -1;
	envs = malloc(sizeof(t_envs **) * ft_mtxlen(__environ));
	while (__environ[++i])
	{
		envs[i]->key = ft_strtrim(__environ[i], "=");
		printf("%i\t-\t%s\n", i, __environ[i]);
	}
	return (NULL);
}


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
			result = ft_strjoin(result, " ");
			result = ft_strjoin(result, getenv(tmp + 1));
		}
		else
			result = ft_strjoin(result, splited_buf[i]);
		free(tmp);
		i++;
	}
	splited_free(splited_buf, i);
	return (result);
}
