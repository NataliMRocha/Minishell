/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/04 15:52:48 by etovaz           ###   ########.fr       */
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
	int		single_quotes;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	single_quotes = ft_handle_quote(buf, '\'');
	while (buf && i < (int)ft_strlen(buf) && buf[i])
	{
		while (single_quotes-- > 0)
			result = ft_strjoin_char(result, buf[i++]);
		if (buf[i] == '$')
			result = result_var(buf, &i, result);
		else
			result = ft_strjoin_char(result, buf[i]);
		i++;
	}
	free(buf);
	return (result);
}
