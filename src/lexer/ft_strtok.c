/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:26 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/26 15:13:08 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
		if (str[i] == '\0')
			return (ft_putendl_fd("syntax error", 2));
	}
	return (0);
}

char	*free_static(char *res, int i, int j)
{
	char	*temp;

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
	if (c == '>' || c == '<' || c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	count_chars(char *res)
{
	int	j;
	int	k;

	j = 0;
	if (res && res[j] && (res[j] == '"' || res[j] == *"'"))
		j = ft_handle_quote(&res[j], res[j]);
	while (res && res[j] && !ft_is_whitespace(res[j]) && !is_symbol(res[j]))
		j++;
	k = 0;
	while (res && res[k] && is_symbol(res[k]))
		k++;
	if (k > 0)
		j = k;
	return (j);
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
