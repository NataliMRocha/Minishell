/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/18 10:40:38 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *test = ft_readline();
	char *toktok = ft_strtok(test);
	free(toktok);
	free(test);

	/*char *test;
	char *toktok;

	while (1)
	{
		test = ft_readline();
		toktok = ft_strtok(test);
		printf("%s\n", toktok);
		while (toktok)
		{
			free(toktok);
			toktok = ft_strtok(NULL);
			printf("%s\n", toktok);
			sleep(1);
		}
		if (strcmp(test, "exit") == 0)
		{
			free(test);
			break;
		}
		else
			free(test);
	} */
}