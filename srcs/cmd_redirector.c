/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:02:40 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/19 14:00:32 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Sets up output redirection, both trunc and append
*/
static int	set_output(t_command *cmd, int i)
{
	if (cmd->outfilename)
	{
		free(cmd->outfilename);
		cmd->outfilename = NULL;
	}
	if ('>' == cmd->orig[i])
	{
		cmd->outputtype = 1;
		i++;
	}
	while (cmd->orig[i] && (SPACE == cmd->orig[i] || '>' == cmd->orig[i]))
		i++;
	while (cmd->orig[i] && SPACE != cmd->orig[i] && '>' != cmd->orig[i])
	{
		cmd->outfilename = add_char_and_free(cmd->outfilename, cmd->orig[i]);
		i++;
	}
	cmd->other_outfilenames = join_and_free(cmd->other_outfilenames,
			ft_strdup(cmd->outfilename));
	cmd->other_outfilenames = add_char_and_free(cmd->other_outfilenames, '\n');
	return (i);
}

/*
	Sets up input redirection, including heredoc
*/
static int	set_input(t_command *cmd, int i)
{
	if ('<' == cmd->orig[i])
	{
		cmd->inputtype = 1;
		i++;
	}
	while (cmd->orig[i] && ' ' == cmd->orig[i])
		i++;
	while (cmd->orig[i] && ' ' != cmd->orig[i])
	{
		cmd->infilename = add_char_and_free(cmd->infilename, cmd->orig[i]);
		i++;
	}
	return (i);
}

/*
	Extracts the optional input and output redirections
*/
static int	find_inputs(t_command *cmd)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	str = NULL;
	len = ft_strlen(cmd->orig);
	while (i < len && cmd->orig[i])
	{
		if ('<' == cmd->orig[i])
			i = set_input(cmd, i + 1);
		if ('>' == cmd->orig[i])
			i = set_output(cmd, i + 1);
		if ('>' == cmd->orig[i])
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
