/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:10:08 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 09:23:33 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Check whether we're dealing with the echo command
*/
static int	is_echo_command(char *str)
{
	return (NULL != ft_strnstr(str, "echo", ft_strlen(str)));
}

/*
	Remove the quotes around commands and arguments
*/
static void	trim_outer_quotes(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	while (++i < mini->cmdc)
	{
		j = -1;
		while (mini->cmds[i].args[++j])
		{
			if ('\'' == mini->cmds[i].args[j][0] ||
				'"' == mini->cmds[i].args[j][0])
			{
				str = ft_strdup(mini->cmds[i].args[j]);
				free(mini->cmds[i].args[j]);
				mini->cmds[i].args[j]
					= ft_strtrim(str, &str[ft_strlen(str) - 1]);
				free(str);
			}
			if (is_echo_command(mini->cmds[i].args[0]))
				break ;
		}
	}
}

static void	trim_orig(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < mini->cmdc)
	{
		tmp = ft_strtrim(mini->cmds[i].orig, " \t\v\a");
		free(mini->cmds[i].orig);
		mini->cmds[i].orig = ft_strdup(tmp);
		free(tmp);
	}
}

void	parse_and_execute(t_mini *mini, char *line)
{
	split_commands(mini, line);
	trim_orig(mini);
	if (!valid_commands(mini))
		return ;
	expand_commands(mini);
	redirect_commands(mini);
	trim_outer_quotes(mini);
	print_commands(mini);
	execute_commands(mini);
}
