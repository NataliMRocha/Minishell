/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/22 12:05:02 by egeraldo         ###   ########.fr       */
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

int	ft_handle_block(char *str, int check_close)
{
	int	i;

	i = 0;
	if (str && str[i] == '(')
		while(str && str[i] && str[++i] != ')')
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
		&& res[i] != '"' && res[i] != '\'' && res[i] != '(')
		i++;
	if (ft_handle_quote(&res[i], 0))
		return (ft_handle_quote(&res[i], 0));
	if(ft_handle_block(&res[i], 0))
		return (ft_handle_block(&res[i], 0));
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
