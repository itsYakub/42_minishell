/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:56:04 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/15 14:10:44 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Copies one command from the whole line
*/
static int	extract_cmd(t_mini *mini, int count, char *line, int len)
{
	char	*sub;
	char	*str;

	sub = ft_substr(line, 0, len);
	str = ft_strdup(sub);
	free(sub);
	mini->commands[count].orig = str;
	return (len + 1);
}

/*
	Splits the whole line into commands based on the non-quoted pipes
*/
static void	extract_cmds(t_mini *mini, char *line)
{
	int	i;
	int	count;
	int	in_apo;
	int	in_quote;
	int	start;

	in_apo = 0;
	in_quote = 0;
	count = -1;
	start = 0;
	i = -1;
	while (line[++i])
	{
		if ('\'' == line[i])
			in_apo = 1 - in_apo;
		if ('"' == line[i])
			in_quote = 1 - in_quote;
		if ('|' == line[i] && 0 == in_apo + in_quote)
			start += extract_cmd(mini, ++count, &line[start], i++ - start);
		if (i == ft_strlen(line) - 1)
			extract_cmd(mini, ++count, &line[start], i++ - start + 1);
	}
}

/*
	Counts the non-quoted pipes and creates a list of commands
*/
static void	divide_commands(t_mini *mini, char *line)
{
	int			i;
	int			count;
	int			in_apo;
	int			in_quote;

	count = 0;
	in_apo = 0;
	in_quote = 0;
	i = -1;
	while (line[++i])
	{
		if ('\'' == line[i])
			in_apo = 1 - in_apo;
		if ('"' == line[i])
			in_quote = 1 - in_quote;
		if ('|' == line[i] && 0 == in_apo + in_quote)
			count++;
	}
	count++;
	mini->commands = malloc(sizeof(t_command) * count);
	mini->cmdc = count;
}

static void	init_commands(t_mini *mini)
{
	int	i;

	i = -1;
	while (++i < mini->cmdc)
	{
		mini->commands[i].infilename = NULL;
		mini->commands[i].inputtype = 0;
		mini->commands[i].outfilename = NULL;
		mini->commands[i].other_outfilenames = NULL;
		mini->commands[i].outputtype = 0;
		mini->commands[i].mini = mini;
	}
}

int	split_commands(t_mini *mini, char *line)
{
	divide_commands(mini, line);
	init_commands(mini);
	extract_cmds(mini, line);
	return (1);
}
