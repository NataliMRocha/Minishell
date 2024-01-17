/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/17 10:30:26 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_is_quote(char *str, char quote)
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

char	*ft_strtok(char *str)
{
	static char	*res;
	int			i;
	int			j;

	if (str)
	{
		res = ft_strdup(str);
		free(str);
	}
	i = 0;
	while (res && res[i] && ft_is_whitespace(res[i]))
		i++;
	j = 0;
	if (res && res[i] && (res[i] == '"' || res[i] == *"'"))
		j = ft_is_quote(&res[i], res[i]);
	while (res && res[j + i] && !ft_is_whitespace(res[j + i]))
		j++;
	str = ft_substr(res, i, j);
	res = res + i + j;
	printf("res: %s\n", res);
	printf("TOKEN: %s\n", str);
	return (str);
}
