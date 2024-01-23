/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/18 17:06:22 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_quote(char *str, char quote)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

char	*free_static(char *res, int i, int j)
{
	char *temp;
	if (res && res[0] == '\0')
		return (NULL);
	temp = ft_strdup(&res[i + j]);
	if (temp && temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
	}
	free(res);
	return (temp);
}

int	is_symbol(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

char	*ft_strtok(char *str, int call)
{
	static char	*res;
	char		*token;
	int			i;
	int			j;

	if (str && call == 0)
		res = ft_strdup(str);
	if (!res)
		return (NULL);
	i = 0;
	while (res && res[i] && ft_is_whitespace(res[i]))
		i++;
	j = 0;
	if (res && res[i] && (res[i] == '"' || res[i] == *"'"))
		j = ft_handle_quote(&res[i], res[i]);
	while (res && res[j + i] && !ft_is_whitespace(res[j + i]))
		j++;
	token = ft_substr(res, i, j);
	res = free_static(res, i, j);
	return (token);
}
