/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:22:21 by egeraldo          #+#    #+#             */
/*   Updated: 2023/07/21 16:19:21 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		len;

	len = ft_strlen(src);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (0);
	len = -1;
	while (src[++len])
		new[len] = src[len];
	new[len] = '\0';
	return (new);
}
