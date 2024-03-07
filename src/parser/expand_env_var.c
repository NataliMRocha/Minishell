/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/07 14:36:52 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*result_var(char *buf, int *i, char *result)
{
	char	*var_name;
	t_envs	*node;

	var_name = ft_strdup("");
	while ((ft_isalnum(buf[*i + 1]) || buf[*i + 1] == '?') && buf[++*i])
		var_name = ft_strjoin_char(var_name, buf[*i]);
	node = ft_getenv(var_name);
	if (node)
		result = ft_strjoin(result, ft_getenv(var_name)->value, 1);
	free(var_name);
	return (result);
}

char	*expand_var(char *buf)
{
	char	*result;
	int		i;
	char	*quotes;
	char	tmp[2];

	i = 0;
	result = ft_calloc(1, sizeof(char));
	tmp[0] = 0;
	if (buf[i] == '\'' || buf[i] == '"')
		tmp[0] = buf[0];
	quotes = ft_strtrim(buf, tmp);
	while (buf && i < (int)ft_strlen(quotes) && quotes[i])
	{
		if (quotes[i] == '$')
			result = result_var(quotes, &i, result);
		else
			result = ft_strjoin_char(result, quotes[i]);
		i++;
	}
	free(buf);
	free(quotes);
	return (result);
}
