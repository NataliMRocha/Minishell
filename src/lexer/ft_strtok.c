/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/14 12:51:55 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_quote(char *str, char quote, int check_close)
{
	int	i;

	i = 0;
	if (str && str[i] && (str[i] == '"' || str[i] == *"'"))
		quote = str[i++];
	while (quote && str && str[i])
	{
		if (str[i++] == quote)
			return (i);
	}
	if (check_close == 1)
		return (0);
	return (i);
}

int	ft_handle_block(char *str, int check_close)
{
	int	i;

	i = 0;
	if (str && str[i] == '(')
		while (str && str[i] && str[++i] != ')')
			;
	if (str && str[i] != ')' && check_close == 1)
		return (0);
	if (str && str[i] == ')')
		i++;
	return (i);
}

int	is_symbol(char *res)
{
	char	*symbols;
	int		j;
	int		i;

	symbols = "><|&";
	i = 0;
	j = 0;
	while (res && res[j] && ft_strchr(symbols, res[j]))
	{
		if (res[j] != res[0])
			i++;
		j++;
	}
	j -= i;
	if (j > 2)
		return (2);
	return (j);
}

int	count_chars(char *res)
{
	int	i;
	int	j;

	i = 0;
	if (i == 0 && (res[i] == '\'' || res[i] == '"'))
		return (ft_handle_quote(&res[i], 0, 0));
	if (i == 0 && ft_handle_block(&res[i], 0))
		return (ft_handle_block(&res[i], 0));
	while (res && res[i] && !is_space(res[i]) && !is_symbol(&res[i])
		&& res[i] != '\'' && res[i] != '"')
		i++;
	i += ft_handle_quote(&res[i], 0, 0);
	if (res && res[i] && res[i] != ' ')
		while (res && res[i] && !is_space(res[i]) && !is_symbol(&res[i]))
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

	if (str && *str && call == 0)
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
