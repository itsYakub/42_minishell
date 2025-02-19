/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:42:31 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 09:38:15 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exit(t_command *cmd)
{
	int	i;
	
	if (1 == cmd->mini->cmdc)
		ft_putstr_fd("exit\n", 2);
	i = -1;
	while (++i < cmd->mini->cmdc)
	{				
		free_stringlist(cmd->mini->commands[i].args);
		free(cmd->mini->commands[i].orig);	
		free(cmd->mini->commands[i].infilename);
		free(cmd->mini->commands[i].outfilename);
		free(cmd->mini->commands[i].other_outfilenames);
		free_stringlist(cmd->mini->env);
		//free(cmd->mini);
	}	
	exit(0);
}
