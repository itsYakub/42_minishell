/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:02:40 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 08:24:50 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Changes the state of inside/outside quotes
*/
static int	set_apoquote(char c, int orig, char apoquote)
{
	if (c == apoquote)
		orig = 1 - orig;
	return (orig);
}

/*
	Extracts the optional input and output redirections
*/
static int	find_inputs(t_command *cmd)
{
	char	*str;
	int		in_apo;
	int		in_quote;
	int		i;

	str = NULL;
	i = 0;
	in_apo = 0;
	in_quote = 0;
	while (i < ft_strlen(cmd->orig) && cmd->orig[i])
	{
		in_apo = set_apoquote(cmd->orig[i], in_apo, '\'');
		in_quote = set_apoquote(cmd->orig[i], in_quote, '"');
		if (1 == set_input(cmd, &i, in_quote, in_apo))
			continue ;
		if (1 == set_output(cmd, &i, in_quote, in_apo))
			continue ;
		str = add_char_and_free(str, cmd->orig[i]);
		i++;
	}
	cmd->args = split_args(str);
	free(str);
	return (1);
}

/*
	Sets up and file redirection
*/
int	redirect_commands(t_mini *mini)
{
	int	i;

	i = -1;
	while (++i < mini->cmdc)
		find_inputs(&mini->commands[i]);
	return (1);
}
