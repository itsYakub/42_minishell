/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:42:31 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 10:53:04 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Checks if the argument contains only numbers
*/
static int	is_a_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

/*
	Replicates the exit command
*/
void	ms_exit(t_command *cmd)
{
	t_mini	*mini;

	mini = cmd->mini;
	if (mini->cmdc > 1)
		return ;
	ft_putstr_fd("exit\n", 2);
	if (cmd->args[1] && 0 == is_a_number(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	ft_free2d((void **)mini->commands->args);
	ft_free2d((void **)mini->env);
	free(mini->commands->orig);
	free(mini->commands->infilename);
	free(mini->commands->outfilename);
	free(mini->commands->other_outfilenames);
	free(mini->commands);
	exit(0);
}
