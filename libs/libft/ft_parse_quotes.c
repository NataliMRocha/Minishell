/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:26:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/02 17:38:27 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_parse_quotes(char *str)
{
	int	i;
	size_t j;
	char *new_str;

	new_str = ft_strdup("");
	i = 0;
	j = 0;
	while(str && str[i])
	{
		if(str[i] == '\'')
		{
			while(str[i] && str[++i] != '\'')
				new_str = ft_strjoin(new_str, ft_chartostr(str[i]));
			i++;
		}
		else if(str[i] == '\"')
		{
			while(str[i] && str[++i] != '\"')
				new_str = ft_strjoin(new_str, ft_chartostr(str[i]));
			i++;
		}
		else
			new_str = ft_strjoin(new_str, ft_chartostr(str[i++]));
	}
	return (new_str);
}
