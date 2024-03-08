/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/08 10:53:44 by natali           ###   ########.fr       */
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

	i = 0;
	result = ft_calloc(1, sizeof(char));
	if (buf[i] == '\'' )
		quotes = ft_strtrim(buf, "'");
	else
		quotes = ft_strtrim(buf, "\'");
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
