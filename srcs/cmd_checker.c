/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:12:15 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 10:22:29 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Checks if all quotes are closed
*/
static int	bad_quotes(char *orig)
{
	int	in_quote;
	int	in_apo;
	int	i;

	in_quote = 0;
	in_apo = 0;
	i = -1;
	while (orig[++i])
	{
		if ('"' == orig[i] && 0 == in_apo)
			in_quote = 1 - in_quote;
		if ('\'' == orig[i] && 0 == in_quote)
			in_apo = 1 - in_apo;
	}
	return (0 != in_quote + in_apo);
}

/*
	Checks a couple of bad inputs
*/
int	valid_commands(t_mini *mini)
{
	int	i;

	i = -1;
	while (++i < mini->cmdc)
	{
		if ('>' == mini->cmds[i].orig[ft_strlen(mini->cmds[i].orig) - 1])
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			mini->exitcode = 1;
			return (0);
		}
		if (1 == bad_quotes(mini->cmds[i].orig))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			mini->exitcode = 1;
			return (0);
		}
	}
	return (1);
}
