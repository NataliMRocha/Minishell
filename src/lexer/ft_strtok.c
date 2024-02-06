/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/06 11:31:45 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str && str[i] && str[0] == quote)
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
	if (res && res[i] && (res[i] == '"' || res[i] == *"'"))
		return (ft_handle_quote(&res[i], res[i]));
	while (res && res[i] && res[0] == '$' && ft_isalnum(res[i + 1]))
		i++;
	if (i > 0)
		return (i + 1);
	while (res && res[i] && !ft_is_whitespace(res[i]) && !is_symbol(&res[i]))
		i++;
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
	while (res && res[i] && ft_is_whitespace(res[i]))
		i++;
	j = count_chars(&res[i]);
	token = ft_substr(res, i, j);
	res = free_static(res, i, j);
	return (token);
}
