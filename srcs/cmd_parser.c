/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:10:08 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 09:15:41 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Returns 1 if valid */
int	parse_and_execute(t_mini *mini, char *line)
{
	int		i;
	int		j;
	char	*str;
	
	split_commands(mini, line);
	expand_commands(mini);
	redirect_commands(mini);
	if (1 == DEBUG)
		check_commands(mini);
	i = -1;
	while (++i < mini->cmdc)
	{
		j = -1;
		while (mini->commands[i].args[++j])
		{
			str = ft_strdup(mini->commands[i].args[j]);
			free(mini->commands[i].args[j]);
			mini->commands[i].args[j] = ft_strtrim(str, "'\"");
			free(str);
		}
	}
	execute_commands(mini);
	return (1);
}
