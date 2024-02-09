/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/08 17:13:40 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_quote(char *str, char quote)
{
	int	i;

	i = 0;
	if (str && str[i] && (str[i] == '"' || str[i] == *"'"))
		quote = str[i++];
	while (str && str[i])
	{
		if (str[i++] == quote)
			return (i);
	}
	return (0);
}

char	*free_static(char *res, int i, int j)
{
	char	*temp;

	if (res && res[0] == '\0')
		return (NULL);
	temp = ft_strdup(&res[i + j]);
	if ((temp && temp[0] == '\0') || ft_strncmp(res, temp, 125) == 0)
	{
		free(temp);
		temp = NULL;
	}
	free(res);
	res = NULL;
	return (temp);
}

int	is_symbol(char *res)
{
	char	*symbols;
	int		j;
	int		i;

	symbols = "><|&()";
	i = 0;
	j = 0;
	while (res && res[j] && ft_strchr(symbols, res[j]))
	{
		if (res[j] != res[j + 1] && ft_strchr(symbols, res[j])
			&& ft_strchr(symbols, res[j + 1]))
			i++;
		j++;
	}
	j -= i;
	return (j);
}

int	count_chars(char *res)
{
	int	i;
	int	j;

	i = 0;
	while (res && res[i] && !is_space(res[i]) && !is_symbol(&res[i])
		&& res[i] != '"' && res[i] != '\'')
		i++;
	i += ft_handle_quote(&res[i], 0);
	if (i > 0)
		return (i);
	j = is_symbol(res);
	if (j > 0)
		i = j;
	return (i);
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
	while (res && res[i] && is_space(res[i]))
		i++;
	j = count_chars(&res[i]);
	token = ft_substr(res, i, j);
	res = free_static(res, i, j);
	return (token);
}
