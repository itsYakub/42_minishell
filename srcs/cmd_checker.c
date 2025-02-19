/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:12:15 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 09:03:59 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check for valid now or later?
int	check_commands(t_mini *mini)
{
	int		i;
	int		j;
	char	**split;

	i = -1;
	printf("cmd count: %i\n", mini->cmdc);
	while (++i < mini->cmdc)
	{
		printf("intype: %i infile: %s outtype: %i outfile: %s\n", mini->commands[i].inputtype, mini->commands[i].infilename, mini->commands[i].outputtype, mini->commands[i].outfilename);
		printf("orig: %s\n", mini->commands[i].orig);
		j = -1;
		while (mini->commands[i].args[++j])
			printf("arg: %s (%i)\n", mini->commands[i].args[j], ft_strlen(mini->commands[i].args[j]));
		if (mini->commands[i].other_outfilenames)
		{
			j = -1;
			split = ft_split(mini->commands[i].other_outfilenames, '\n');
			while (split[++j])
				printf("out filename: %s\n", split[j]);
			free_stringlist(split);
		}
	}
	return (1);
}
