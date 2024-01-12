/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:59:36 by egeraldo          #+#    #+#             */
/*   Updated: 2023/12/14 17:29:58 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*aux;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)ft_calloc(len, sizeof(char));
	if (join == NULL)
		return (NULL);
	aux = join;
	while (*s1 != '\0')
		*aux++ = *s1++;
	while (*s2 != '\0')
		*aux++ = *s2++;
	*aux = '\0';
	return (join);
}
