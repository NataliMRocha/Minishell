/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:40:11 by etovaz            #+#    #+#             */
/*   Updated: 2024/03/13 17:55:26 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = ft_calloc(1024, sizeof(char));
	getcwd(path, 1024);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (update_status_error(0));
}
