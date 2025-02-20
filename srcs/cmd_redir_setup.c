/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:17:42 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 15:44:50 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_old_outfilename(t_command *cmd)
{
	if (cmd->outname)
	{
		free(cmd->outname);
		cmd->outname = NULL;
	}
}

/*
	Sets up output redirection, both trunc and append
*/
int	set_output(t_command *cmd, int *start, int in_quote, int in_apo)
{
	int	i;

	i = *start;
	if ('>' == cmd->orig[i] && 0 == (in_quote + in_apo))
	{
		i++;
		free_old_outfilename(cmd);
		if ('>' == cmd->orig[i])
		{
			cmd->outputtype = 1;
			i++;
		}
		while (cmd->orig[i] && (SPACE == cmd->orig[i] || '>' == cmd->orig[i]))
			i++;
		while (cmd->orig[i] && SPACE != cmd->orig[i] && '>' != cmd->orig[i])
			cmd->outname = add_char_and_free(cmd->outname, cmd->orig[i++]);
		cmd->other_outnames = join_and_free(cmd->other_outnames,
				ft_strdup(cmd->outname));
		cmd->other_outnames = add_char_and_free(cmd->other_outnames, '\n');
		*start = i;
		return (1);
	}
	return (0);
}

static void	free_old_infilename(t_command *cmd)
{
	if (cmd->infilename)
	{
		free(cmd->infilename);
		cmd->infilename = NULL;
	}
}

/*
	Sets up input redirection, including heredoc
*/
int	set_input(t_command *cmd, int *start, int in_quote, int in_apo)
{
	int	i;

	i = *start;
	if ('<' == cmd->orig[i] && 0 == (in_quote + in_apo))
	{
		free_old_infilename(cmd);
		i++;
		if ('<' == cmd->orig[i])
		{
			cmd->inputtype = 1;
			i++;
		}
		while (cmd->orig[i] && ' ' == cmd->orig[i])
			i++;
		while (cmd->orig[i] && ' ' != cmd->orig[i] && '<' != cmd->orig[i])
		{
			cmd->infilename = add_char_and_free(cmd->infilename, cmd->orig[i]);
			i++;
		}
		*start = i;
		return (1);
	}
	return (0);
}
