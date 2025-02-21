/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:10:08 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/21 08:33:54 by lwillis          ###   ########.fr       */
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
		while (mini->commands[i].args[++j])
		{
			if ('\'' == mini->commands[i].args[j][0] ||
				'"' == mini->commands[i].args[j][0])
			{
				str = ft_strdup(mini->commands[i].args[j]);
				free(mini->commands[i].args[j]);
				mini->commands[i].args[j]
					= ft_strtrim(str, &str[ft_strlen(str) - 1]);
				free(str);
			}
			if (is_echo_command(mini->commands[i].args[0]))
				break ;
		}
	}
}

static int	invalid_output_redir(char *str)
{
	int	len;
	int	unprint_count;
	char	*tmp;
	
	tmp = ft_strrchr(str, '>');
	len = ft_strlen(tmp);
	
	return (1);
}

/* Returns 1 if valid */
int	parse_and_execute(t_mini *mini, char *line)
{
	split_commands(mini, line);
	invalid_output_redir(mini->commands[0].orig);
	printf("%s %i %i\n", mini->commands[0].orig, NULL == mini->commands[0].orig, mini->commands[0].orig[0]);
	expand_commands(mini);
	printf("%s %i %i\n", mini->commands[0].orig, NULL == mini->commands[0].orig, mini->commands[0].orig[0]);
	redirect_commands(mini);
	printf("%s %i %i\n", mini->commands[0].orig, NULL == mini->commands[0].orig, mini->commands[0].orig[0]);
	trim_outer_quotes(mini);
	printf("%s %i %i\n", mini->commands[0].orig, NULL == mini->commands[0].orig, mini->commands[0].orig[0]);
	if (1 == DEBUG)
		check_commands(mini);
	execute_commands(mini);
	return (1);
}
