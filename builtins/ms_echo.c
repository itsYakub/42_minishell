/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:22:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 09:30:42 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_echo(t_cmd cmd)
{
	char	*str;
	int		skip_nl;
	int		nbr_cmds;
	int		i;

	str = cmd.cmd[1];
	skip_nl = 0;
	if (!str)
	{
		printf("\n");
		return ;
	}
	nbr_cmds = -1;
	while (cmd.cmd[++nbr_cmds]) ;
	skip_nl = nbr_cmds > 1 && cmd_equals("-n", cmd.cmd[1]);
	i = 0 + skip_nl;
	while (++i < nbr_cmds)
	{
		printf("%s", cmd.cmd[i]);
		if (i != nbr_cmds - 1)
			printf(" ");
	}
	if (!skip_nl)
		printf("\n");
}
