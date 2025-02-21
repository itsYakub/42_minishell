/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:05:50 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 08:23:04 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	Replaces a $var with whatever is in the env list
*/
static char	*replace_var(char *var_name, char *str, t_mini *mini, int in_quote)
{
	char	*tmp;
	int		j;

	j = -1;
	tmp = env_value(var_name, mini, in_quote);
	while (tmp && tmp[++j])
		str = add_char_and_free(str, tmp[j]);
	free(tmp);
	return (str);
}

/*
	Replaces all valid (not inside single quotes) env vars
*/
static char	*expand_cmd(t_command *cmd, t_mini *mini)
{
	int		i;
	int		in_apo;
	char	*str;
	int		in_quote;

	i = -1;
	in_apo = 0;
	in_quote = 0;
	str = NULL;
	while (cmd->orig[++i])
	{
		if ('\'' == cmd->orig[i] && 0 == in_quote)
			in_apo = 1 - in_apo;
		if ('"' == cmd->orig[i])
			in_quote = 1 - in_quote;
		if ('$' == cmd->orig[i] && 0 == in_apo && SPACE != cmd->orig[i + 1]
			&& '\0' != cmd->orig[i + 1])
		{
			str = replace_var(&cmd->orig[i + 1], str, mini, in_quote);
			i += env_length(&cmd->orig[i + 1]) + 1;
		}
		else
		{
			str = add_char_and_free(str, cmd->orig[i]);
		}
	}
	return (str);
}

/*
	Replaces all instance of $vars unless inside apostrophes
*/
int	expand_commands(t_mini *mini)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < mini->cmdc)
	{
		str = expand_cmd(&mini->commands[i], mini);
		free(mini->commands[i].orig);
		if (str)
		{
			mini->commands[i].orig = ft_strdup(str);
			free(str);
		}
		else
			mini->commands[i].orig = ft_strdup("");
	}
	return (1);
}
