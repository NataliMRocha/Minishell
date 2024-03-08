/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/08 17:08:32 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*result_var(char *buf, int *i, char *result)
{
	char	*var_name;
	t_envs	*node;

	if (buf[*i + 1] == '?')
	{
		*i = *i + 1;
		return (ft_strjoin(result, ft_itoa(update_status_error(-1)), 1));
	}
	var_name = ft_strdup("");
	while ((ft_isalnum(buf[*i + 1]) || buf[*i + 1] == '?') && buf[++*i])
		var_name = ft_strjoin_char(var_name, buf[*i]);
	node = ft_getenv(var_name);
	if (node)
		result = ft_strjoin(result, node->value, 1);
	free(var_name);
	return (result);
}
char	*trim_single_quotes(char *buf)
{
	char	*quotes;

	quotes = ft_strtrim(buf, "'");
	free(buf);
	return (quotes);
}

char	*expand_var(char *buf)
{
	char	*result;
	char	*quotes;
	int		i;

	i = 0;
	if (buf && buf[i] == '\'')
		return (trim_single_quotes(buf));
	quotes = ft_remove_quotes(buf);
	result = ft_calloc(1, sizeof(char));
	while (quotes && i < (int)ft_strlen(quotes) && quotes[i])
	{
		if (quotes[i] == '$' && quotes[i + 1] != '\0' && quotes[i + 1] != ' ')
			result = result_var(quotes, &i, result);
		else
			result = ft_strjoin_char(result, quotes[i]);
		i++;
	}
	free(buf);
	free(quotes);
	return (result);
}
