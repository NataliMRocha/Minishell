/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:28:13 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/18 13:35:01 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	/* char *test = ft_readline();
	char *toktok = ft_strtok(test, 0);
	free(toktok);
	toktok = ft_strtok(test, 1);
	free(toktok);
	free(test); */

	char *test;
	char *toktok;
	int call = 0;

	test = "";
	while (1)
	{
		test = ft_readline();
		toktok = " ";
		while (toktok && toktok[0] != '\0')
		{
			if (toktok && *toktok != ' ')
				free(toktok);
			toktok = ft_strtok(test, call++);
			printf("%s\n", toktok);
		}
		if (strcmp(test, "exit") == 0)
		{
			free(test);
			break;
		}
		else
		{
			call = 0;
			free(test);
		}
	}
}