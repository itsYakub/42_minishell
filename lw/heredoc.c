/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:01 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/10 11:52:18 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_cmd *cmd)
{
	char	*line;
	char	*limiter = "stop";
	(void)cmd;

	while (1)
	{
		line = readline("heredoc>");
		if (0 == ft_strcmp(line, limiter))
		{
			free(line);
			exit (0);
		}
		if (line)
		{
			//write(p_fd[1], line, lw_strlen(line));
			printf("Found line\n");
			free(line);
		}
	}
}
