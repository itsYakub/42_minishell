/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:22:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/12 14:58:57 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_echo(t_cmd *cmd)
{
	char	*str;
	int		skip_nl;
	int		cmd_count;
	int		i;

	str = cmd->args[1];
	skip_nl = 0;
	if (!str)
	{
		ft_putstr_fd("\n", cmd->rdrfd[1]);
		return ;
	}
	cmd_count = -1;
	while (cmd->args[++cmd_count])
		;
	skip_nl = cmd_count > 1
		&& !ft_strncmp("-n", *cmd->args + 1, ft_strlen(*cmd->args + 1));
	i = 0 + skip_nl;
	while (++i < cmd_count)
	{
		ft_putstr_fd(cmd->args[i], cmd->rdrfd[1]);
		if (i != cmd_count - 1)
			ft_putstr_fd(" ", cmd->rdrfd[1]);
	}
	if (!skip_nl)
		ft_putstr_fd("\n", cmd->rdrfd[1]);
}
