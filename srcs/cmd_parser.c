/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:10:08 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/15 16:05:39 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Returns 1 if valid */
int	parse_and_execute(t_mini *mini, char *line)
{
	split_commands(mini, line);
	expand_commands(mini);
	redirect_commands(mini);
	//check_commands(mini);
	execute_commands(mini);
	return (1);
}
