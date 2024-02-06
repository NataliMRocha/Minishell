/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:26:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/05 18:57:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_remove_quotes(char *str)
{
	int		i;
	char	*new_str;
	char	quote;

	new_str = ft_strdup("");
	i = 0;
	while(str && str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			while(str[i] && str[++i] != quote)
				new_str = ft_strjoin_char(new_str, str[i]);
			i++;
		}
		else
			new_str = ft_strjoin_char(new_str, str[i++]);
	}
	return (new_str);
}
