/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:22:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 09:57:11 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_echo(t_cmd cmd)
{
	char	*str;
	int		skip_nl;
	int		cmd_count;
	int		i;

	str = cmd.cmd[1];
	skip_nl = 0;
	if (!str)
	{
		printf("\n");
		return ;
	}
	cmd_count = -1;
	while (cmd.cmd[++cmd_count])
		;
	skip_nl = cmd_count > 1 && cmd_equals("-n", cmd.cmd[1]);
	i = 0 + skip_nl;
	while (++i < cmd_count)
	{
		printf("%s", cmd.cmd[i]);
		if (i != cmd_count - 1)
			printf(" ");
	}
	if (!skip_nl)
		printf("\n");
}
