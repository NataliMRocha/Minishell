/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:33:12 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/18 16:36:26 by etovaz           ###   ########.fr       */
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
		result = ft_strjoin(result, ft_itoa(update_status_error(-1)), 3);
		return (result);
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
	if (!on_heredoc(-1))
		quotes = ft_remove_quotes(buf);
	else
		quotes = ft_strdup(buf);
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

char	**expanded_variable(char **cmd_list)
{
	char	**expanded;
	int		i;
	int		j;

	i = -1;
	expanded = NULL;
	while (cmd_list && cmd_list[++i])
		cmd_list[i] = expand_var(cmd_list[i]);
	expanded = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (cmd_list[++i])
		if (*cmd_list[i])
			expanded[j++] = ft_strdup(cmd_list[i]);
	free_split(cmd_list);
	cmd_list = NULL;
	return (expanded);
}
