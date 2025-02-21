/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 09:22:09 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 09:23:16 by lwillis          ###   ########.fr       */
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
		cmd->outputtype, cmd->outname);
	printf("others: %s\n", cmd->other_outnames);
}

/*
	For debug to make sure we're parsing what we should be
*/
void	print_commands(t_mini *mini)
{
	int		i;
	int		j;
	char	**split;

	if (0 == DEBUG)
		return ;
	i = -1;
	printf("cmd count: %i\n", mini->cmdc);
	while (++i < mini->cmdc)
	{
		print_redirection(&mini->cmds[i]);
		printf("orig: %s\n", mini->cmds[i].orig);
		j = -1;
		while (mini->cmds[i].args[++j])
			printf("arg: %s (%i)\n", mini->cmds[i].args[j],
				ft_strlen(mini->cmds[i].args[j]));
		if (mini->cmds[i].other_outnames)
		{
			j = -1;
			split = ft_split(mini->cmds[i].other_outnames, '\n');
			while (split[++j])
				printf("out filename: %s\n", split[j]);
			ft_free2d((void **) split);
		}
	}
}
