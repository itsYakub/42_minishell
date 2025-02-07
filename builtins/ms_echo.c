/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:22:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 15:23:48 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_echo(t_mini *mini)
{
	char	*str;
	int		skip_nl;
	int		cmd_count;
	int		i;

	str = mini->cmd->cmd[1];
	skip_nl = 0;
	if (!str)
	{
		ft_putstr_fd("\n", mini->cmd->fd1);
		return ;
	}
	cmd_count = -1;
	while (mini->cmd->cmd[++cmd_count])
		;
	skip_nl = cmd_count > 1 && cmd_equals("-n", mini->cmd->cmd[1]);
	i = 0 + skip_nl;
	while (++i < cmd_count)
	{
		ft_putstr_fd(mini->cmd->cmd[i], mini->cmd->fd1);
		if (i != cmd_count - 1)
			ft_putstr_fd(" ", mini->cmd->fd1);
	}
	if (!skip_nl)
		ft_putstr_fd("\n", mini->cmd->fd1);
}
