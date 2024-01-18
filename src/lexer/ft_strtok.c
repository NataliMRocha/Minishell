/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/18 10:46:40 by egeraldo         ###   ########.fr       */
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
	printf("RES: %s | I: %d | J: %d | LEN %zu\n", res, i, j, ft_strlen(res));
	temp = ft_strdup(&res[i + j]);
	free(res);
	return (temp);
}

char	*ft_strtok(char *str)
{
	static char	*res;
	char		*token;
	int			i;
	int			j;

	if (str)
		res = ft_strdup(str);
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
	if (res && res[0] == '\0')
		free (res);
	return (token);
}
