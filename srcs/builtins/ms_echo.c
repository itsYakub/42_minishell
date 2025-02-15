/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:22:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/15 14:05:59 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Sets whether the quote should be printed
*/
static int	set_quote_state(char *quote, char current)
{
	if (SPACE == *quote)
	{
		*quote = current;
		return (1);
	}
	else if (*quote == current)
	{
		*quote = SPACE;
		return (1);
	}
	return (0);
}

/*
	Print out all the arguments, handling quotation marks/apostrophes
*/
static void	print_args(t_command *cmd, int arg_count, int skip_nl)
{
	int		i;
	int		j;
	char	quote;

	i = 0 + skip_nl;
	j = -1;
	while (++i < arg_count)
	{
		quote = SPACE;
		while (cmd->args[i][++j])
		{
			if ('\'' == cmd->args[i][j] || '"' == cmd->args[i][j])
			{
				if (set_quote_state(&quote, cmd->args[i][j]))
					continue ;
			}
			write(1, &cmd->args[i][j], 1);
		}
		if (i != arg_count - 1)
			printf(" ");
	}
}

/*
	Replicates the echo command, needs to strip quotation marks.
	If the first argument is -n don't add a newline
*/
void	ms_echo(t_command *cmd)
{
	char	*str;
	int		skip_nl;
	int		arg_count;

	str = cmd->args[1];
	skip_nl = 0;
	if (!str)
	{
		printf("\n");
		return ;
	}
	arg_count = -1;
	while (cmd->args[++arg_count])
		;
	skip_nl = arg_count > 1
		&& !ft_strncmp("-n", *cmd->args + 1, ft_strlen(*cmd->args + 1));
	print_args(cmd, arg_count, skip_nl);
	if (!skip_nl)
		printf("\n");
}
