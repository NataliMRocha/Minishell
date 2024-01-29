/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:59:36 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/29 18:41:56 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)ft_calloc(len, sizeof(char));
	if (join == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		join[i] = s2[j];
	join[i + j] = '\0';
	free((void *)s1);
	return (join);
}
