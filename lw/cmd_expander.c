/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:05:50 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/14 13:53:51 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Returns how long an env var name is
*/
static int	env_length(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || '_' == str[i]))
		i++;
	return (i);
}

/*
	Replaces all valid (not inside single quotes) env vars
*/
static char	*expand_cmd(t_command *cmd, t_mini *mini)
{
	int		i;
	int		j;
	int		in_apo;
	char	*str;
	char	*tmp;

	i = -1;
	in_apo = 0;
	str = NULL;
	while (cmd->orig[++i])
	{
		if ('\'' == cmd->orig[i])
			in_apo = 1 - in_apo;
		if ('$' == cmd->orig[i] && 0 == in_apo)
		{
			j = -1;
			tmp = env_value(&cmd->orig[i + 1], mini);
			while (tmp && tmp[++j])
				str = add_char_and_free(str, tmp[j]);
			i += env_length(&cmd->orig[i + 1]) + 1;
			free(tmp);
		}
		else
			str = add_char_and_free(str, cmd->orig[i]);
	}
	return (str);
}

int	expand_commands(t_mini *mini)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < mini->cmdc)
	{
		str = expand_cmd(&mini->commands[i], mini);
		free(mini->commands[i].orig);
		mini->commands[i].orig = ft_strdup(str);
		free(str);
	}
	return (1);
}
