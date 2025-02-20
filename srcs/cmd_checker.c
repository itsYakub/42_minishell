/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:12:15 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 09:59:49 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Prints the redirection status
*/
static void	print_redirection(t_command *cmd)
{
	printf("intype: %i infile: %s outtype: %i outfile: %s\n",
		cmd->inputtype, cmd->infilename,
		cmd->outputtype, cmd->outfilename);
	printf("others: %s\n", cmd->other_outfilenames);
}

/*
	Mainly for debug to make sure we're parsing what we should be
*/
void	check_commands(t_mini *mini)
{
	int		i;
	int		j;
	char	**split;

	i = -1;
	printf("cmd count: %i\n", mini->cmdc);
	while (++i < mini->cmdc)
	{
		print_redirection(&mini->commands[i]);
		printf("orig: %s\n", mini->commands[i].orig);
		j = -1;
		while (mini->commands[i].args[++j])
			printf("arg: %s (%i)\n", mini->commands[i].args[j],
				ft_strlen(mini->commands[i].args[j]));
		if (mini->commands[i].other_outfilenames)
		{
			j = -1;
			split = ft_split(mini->commands[i].other_outfilenames, '\n');
			while (split[++j])
				printf("out filename: %s\n", split[j]);
			ft_free2d((void **) split);
		}
	}
}
